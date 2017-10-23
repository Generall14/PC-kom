#include "ZR3ReadFile.hpp"
#include <QCoreApplication>
#include <QDebug>

ZR3ReadFile::ZR3ReadFile(uchar header):
    _header(header)
{
}

ZR3ReadFile::~ZR3ReadFile()
{

}

void ZR3ReadFile::OnStop()
{
    delete timer;
}

void ZR3ReadFile::OnStart()
{
    timer = new QTimer(NULL);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &ZR3ReadFile::timeouted);
    connect(this, SIGNAL(StopTimer()), timer, SLOT(stop()), Qt::QueuedConnection);
    Send();
}

void ZR3ReadFile::timeouted()
{
    if(!--miss)
    {
        emit Error("Nie można odczytać pliku");
        emit Done(_header, QByteArray());
        Stop();
        return;
    }
}

void ZR3ReadFile::Send()
{
    QByteArray temp;
    temp.append(_header);
    temp.append((curroffset>>8)&0xFF);
    temp.append(curroffset&0xFF);
    temp.append(0x3F);
    emit SendDataFrame(temp);
    timer->start(1200);
}

void ZR3ReadFile::RecievedData(QByteArray data)
{
    if((uint8_t)data.at(0)==(_header|0x80))
    {
        data.remove(0, 1);
        temp.append(data);
        emit StopTimer();
        if(data.size()<63)
        {
            emit Done(_header, temp);
            Stop();
        }
        else
        {
            curroffset += 63;
            miss = MAX_MISSES;
        }
    }
}

void ZR3ReadFile::Run()
{
    QThread::msleep(10);
    if((!timer->isActive())&&(miss)&&(!stopRequest))
        Send();
    QCoreApplication::processEvents();
}
