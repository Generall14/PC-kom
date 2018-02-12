#include "StawrovLogger.hpp"

STawrovLogger::STawrovLogger(QString fileName, QObject* parent):
    QObject(parent)
{
    low = "tlo\n";
    high = "cos\n";

    logStream.setDevice(&logFile);
    Reset(fileName);
    timer = new QTimer();
    timer->setInterval(3000);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(StopMeaning()), Qt::QueuedConnection);
}

STawrovLogger::~STawrovLogger()
{
    logFile.close();
    delete timer;
}

void STawrovLogger::Reset(QString fileName)
{
    logFile.close();
    _state = state_reseted;

    logFile.setFileName(fileName);
    if(!logFile.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        emit Error(QString("Nie można otworzyć pliku %1.").arg(fileName));
        logFile.close();
        return;
    }

    meanv.clear();
    meanc = 0;
    curretChannels = 0;
    emit SetChannels(curretChannels);
    emit StateChanged("noninitialized");
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
            _state = state_collecting_mean;
            curretChannels = channels.size();
            meanv = channels;
            meanc = 1;
            timer->start();
            emit StateChanged("zbieranie średniej");
            emit SetChannels(curretChannels);
        }
        else
        {
            logStream << high;
            _state = state_collecting_meat;
            curretChannels = channels.size();
            emit StateChanged("zbieranie mięsa");
            emit SetChannels(curretChannels);
        }
        break;
    case state_collecting_mean:
        if(zajety)
            StopMeaning();
        break;
    case state_collecting_background:
        if(zajety)
        {
            logStream << high;
            _state = state_collecting_meat;
            emit StateChanged("zbieranie mięsa");
        }
        AppendLine(channels, "CS");
        break;
    case state_collecting_meat:
        if(!zajety)
        {
            logStream << low;
            _state = state_collecting_background;
            emit StateChanged("zbieranie tła");
        }
        AppendLine(channels, "CS");
        break;
    default:
        _state = state_reseted;
        emit Error("Coś się skasztaniło");
        break;
    }
}

void STawrovLogger::StopMeaning()
{
    if((!meanv.isEmpty())&&(meanc))
    {
        for(int i=0;i<meanv.size();++i)
            meanv[i] = meanv[i]/meanc;
        AppendLine(meanv, "CB");
    }
    _state = state_collecting_background;
    emit StateChanged("zliczenia tła");
}

void STawrovLogger::AppendLine(QList<int> v, QString pre)
{
    for(int i: v)
        pre.append(QString(",%1").arg(i, 6, 10, QChar('0')));
    pre.append("\n");
    logStream << pre;
}
