#include "StawrovLogger.hpp"
#include "QDir"
#include <QDebug>
#include <iostream>
#include <QDate>
#include <QTime>

STawrovLogger::STawrovLogger(QObject* parent):
    QObject(parent)
{
    low = "occ_off\n";
    high = "AAA\n";

    QDir cdir("./Pomiary/");
    if (!cdir.exists())
        cdir.mkpath(".");

    logStream.setDevice(&logFile);
}

STawrovLogger::~STawrovLogger()
{
    logFile.close();
}

void STawrovLogger::Reset(QString fileName)
{
    fileName = fileName.insert(0, "Pomiary/");

    logFile.setFileName(fileName);
    if(logFile.exists())
    {
        int add = 1;
        QString pre = fileName.left(fileName.lastIndexOf('.'));
        QString suff = fileName.mid(fileName.lastIndexOf('.'));
        while(logFile.exists())
            logFile.setFileName(pre+"_"+QString::number(add++)+suff);
    }

    fileName = fileName.insert(0, "Pomiary/");

    if(logFile.open(QIODevice::Text | QIODevice::Append))
    {
        logStream << high;
        logFile.close();
    }

//    if(!logFile.open(QIODevice::Text | QIODevice::Append))
//    {
//        emit Error(QString("Nie można otworzyć pliku %1.").arg(fileName));
//        logFile.close();
//        emit File("---");
//        return;
//    }
    emit File(logFile.fileName());
}

void STawrovLogger::FrameReaded(QSharedPointer<Frame> frame)
{
    if(!frame->isValid())
        return;
    QByteArray cargo = frame->pureData().mid(4);
    if((cargo.at(0)-0x31)!=0)
        return;
    if(cargo.size()<6)
        return;

    bool zajety = false;
    if(cargo.at(1)&&0x01)
        zajety = true;

    QList<int> temp;
    cargo.remove(0, 3);
    while(cargo.size()>1)
    {
        int tval = 0;
        tval |= (cargo.at(1)<<8)&0xFF00;
        tval |= (cargo.at(0)<<0)&0x00FF;
        temp.append(tval);
        cargo.remove(0, 2);
    }

    if(ignoringFirstChannel&&temp.size()>0)
        temp.removeFirst();

//    for(int i:temp)
//    {
//        if(i>255)
//            return;
//    }

    if(!push)
    {
        acc=temp;
        push = true;
    }
    else
    {
        push=false;
        if(temp.size()!=acc.size())
        {
            OccReset();
        }
        else
        {
            for(int i=0;i<temp.size();i++)
                acc[i] += temp[i];
            for(int i:acc)
            {
                if(i>3000)
                {
                    acc.clear();
                    return;
                }
            }
            DoSomeStuff(acc, zajety);
            addToMean(acc);
        }
        acc.clear();
    }
}

void STawrovLogger::DoSomeStuff(QList<int> channels, bool zajety)
{
    switch (_state)
    {
    case state_reseted:
        if(!zajety)
            _state = state_collecting_background;
        break;
    case state_collecting_background:
        if(zajety)
        {
            OccOn();
        }
        else
        {
            if(trash.size()<15)
            {
                trash.append(channels);
                break;
            }
            shortData.push_back(channels);
            if(shortData.size()>15)
            {
                longData.push_back(shortData.at(0));
                shortData.removeFirst();
                if(longData.size()>600)
                    longData.removeFirst();
            }
        }
        break;
    case state_collecting_meat:
        if(!zajety)
        {
            OccOff();
        }
        else
        {
            occData.append(channels);
        }
    }
}

void STawrovLogger::OccOn()
{
    _state = state_collecting_meat;
    emit StateChanged("zbieranie mięsa");
}

void STawrovLogger::skip()
{
    _state = state_reseted;
    trash.clear();
    occData.clear();
    qDebug() << "skip()";
    emit StateChanged("reseted");
}

void STawrovLogger::OccOff()
{
    _state = state_collecting_background;
    if(longData.size()<5)
    {
        skip();
        return;
    }
    if(shortData.size()<15)
    {
        skip();
        return;
    }
    mean.clear();
    mean = longData.at(0);
    for(int i=1;i<longData.size();i++)
    {
        if(mean.size()!=longData.at(i).size())
        {
            OccReset();
            return;
        }
        for(int j=0;j<mean.size();j++)
            mean[j] += longData[i][j];
    }
    for(int j=0;j<mean.size();j++)
        mean[j] = (mean[j]*5)/(longData.size());

    toFile();
    emit StateChanged("zbieranie tła");
    trash.clear();
    occData.clear();
}

void STawrovLogger::OccReset()
{
    _state = state_reseted;
    qDebug() << "OccReset()";
    emit StateChanged("reseted");
    longData.clear();
    occData.clear();
}

void STawrovLogger::toFile()
{
    if(!logFile.open(QIODevice::Text | QIODevice::Append))
    {
        emit Error(QString("Nie można otworzyć pliku %1.").arg(logFile.fileName()));
        logFile.close();
        emit File("---");
        return;
    }

    qDebug() << "toFile()";
//    logStream << high;
    QString pre;
    for(int i=0;i<mean.size();++i)
    {
        if(i!=0)
            pre.append(",");
        pre.append(QString("%1").arg(mean.at(i), 6, 10, QChar('0')));
    }
    pre.append("\n");
    logStream<<pre;

    pre.clear();
    for(QList<int> aaa: shortData)
    {
        for(int i=0;i<aaa.size();++i)
        {
            if(i!=0)
                pre.append(",");
            pre.append(QString("%1").arg(aaa.at(i), 6, 10, QChar('0')));
        }
        pre.append("\n");
    }
    logStream<<pre;

    pre.clear();
    for(QList<int> aaa: occData)
    {
        for(int i=0;i<aaa.size();++i)
        {
            if(i!=0)
                pre.append(",");
            pre.append(QString("%1").arg(aaa.at(i), 6, 10, QChar('0')));
        }
        pre.append("\n");
    }
    logStream<<pre;
    logStream << high;

    logFile.close();
}

void STawrovLogger::AppendLine(QList<int> v)
{
    QString pre;
    for(int i=0;i<v.size();++i)
    {
        if(i!=0)
            pre.append(",");
        pre.append(QString("%1").arg(v.at(i), 6, 10, QChar('0')));
    }
    pre.append("\n");
    logStream << pre;
    if(writen++>10)
    {
        writen = 0;
        logStream.flush();
    }
}

void STawrovLogger::addToMean(QList<int>& newvals)
{
    if(!meaning)
        return;
    while(total.size()<newvals.size())
        total.append(0);
    for(int i=0;i<newvals.size();i++)
        total[i] += newvals[i];
    counts++;
}

void STawrovLogger::startMeaning()
{
    meaning = true;
    total.clear();
    counts = 0;
}

void STawrovLogger::stopMeaning()
{
    meaning = false;

    if(!counts)
        return;

    QFile file("Pomiary/mean.ods");
    if(!file.open(QIODevice::Text | QIODevice::Append))
    {
        emit Error(QString("Nie można otworzyć pliku %1.").arg(file.fileName()));
        file.close();
        return;
    }
    QTextStream stream(&file);
    stream << QDate::currentDate().toString() << "  " << QTime::currentTime().toString() << "\r\n" << meanString();
    file.close();

    counts = 0;
}

void STawrovLogger::displayMean()
{
    std::cout << meanString().toStdString() << std::flush;
}

QString STawrovLogger::meanString()
{
    int sum = 0;
    for(auto i: total)
        sum += i;
    QString temp = QString("Liczba pomiarow: %1\r\nZliczenia (suma = %2): ;").arg(counts).arg(sum);
    for(auto i: total)
        temp.append(QString("%1;").arg(i));
    temp.append(QString("\r\nUsrednione (suma = %1): ;").arg(float(sum)/float(counts)*float(5), 0, 'f', 2));
    for(auto i: total)
        temp.append(QString("%1;").arg(float(i)/float(counts)*float(5), 0, 'f', 2));
    temp.append("\r\n\r\n");
    return temp;
}

void STawrovLogger::setIgnoringFirstChannel(bool ignore)
{
    ignoringFirstChannel = ignore;
}
