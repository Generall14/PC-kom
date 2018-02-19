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
    high = "occ_on\n";

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
    logFile.close();
    _state = state_reseted;

    logFile.setFileName(fileName);
    if(logFile.exists())
    {
        int add = 1;
        QString pre = fileName.left(fileName.lastIndexOf('.'));
        QString suff = fileName.mid(fileName.lastIndexOf('.'));
        while(logFile.exists())
            logFile.setFileName(pre+"_"+QString::number(add++)+suff);
    }

    if(!logFile.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        emit Error(QString("Nie można otworzyć pliku %1.").arg(fileName));
        logFile.close();
        emit File("---");
        return;
    }
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

    addToMean(temp);
    DoSomeStuff(temp, zajety);
}

void STawrovLogger::DoSomeStuff(QList<int> channels, bool zajety)
{
    switch (_state)
    {
    case state_reseted:
        if(!zajety)
        {
            logStream << low;
            curretChannels = channels.size();
            _state = state_collecting_background;
            emit SetChannels(curretChannels);
            emit StateChanged("zbieranie tła");
        }
        else
        {
            logStream << high;
            curretChannels = channels.size();
            _state = state_collecting_meat;
            emit StateChanged("zbieranie mięsa");
            emit SetChannels(curretChannels);
        }
        break;
    case state_collecting_background:
        if(zajety)
        {
            logStream << high;
            _state = state_collecting_meat;
            emit StateChanged("zbieranie mięsa");
        }
        AppendLine(channels);
        break;
    case state_collecting_meat:
        if(!zajety)
        {
            logStream << low;
            _state = state_collecting_background;
            emit StateChanged("zbieranie tła");
        }
        AppendLine(channels);
        break;
    default:
        _state = state_reseted;
        emit Error("Coś się skasztaniło");
        break;
    }
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

    QFile file("Pomiary/mean.txt");
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
    QString temp = QString("Liczba pomiarow: %1\r\nZliczenia: ").arg(counts);
    for(auto i: total)
        temp.append(QString("[%1]  ").arg(i));
    temp.append("\r\nUsrednione: ");
    for(auto i: total)
        temp.append(QString("[%1]  ").arg(float(i)/float(counts), 0, 'f', 2));
    temp.append("\r\n\r\n");
    return temp;
}
