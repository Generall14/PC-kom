#include "FrameBuilderZR3.hpp"
#include "../Factory.hpp"
#include <QDebug>
#include <QThread>
#include <QCoreApplication>
#include "../Frame_imp/FrameZR3.hpp"

FrameBuilderZR3::FrameBuilderZR3(uchar myAdr, uchar nextAdr, bool slw):
    _myAdr(myAdr),
    _nextAdr(nextAdr),
    _slowly(slw)
{
    Desc::description = "FrameBuilderZR3";

    if(slw)
        haveToken = true;

    qsrand((int)QThread::currentThreadId());
    for(int i=0;i<10;++i)
        _serial.append(0x41+qrand()%25);

    InitTokenFrame();
}

void FrameBuilderZR3::InitTokenFrame()
{
    tokenFrame.clear();
    tokenFrame.append(0xfd);
    tokenFrame.append(0x80);
    tokenFrame.append(_nextAdr);
    tokenFrame.append(_myAdr);
    FrameZR3::AppendCRC(tokenFrame);
}

void FrameBuilderZR3::OnStart()
{
    timer = new QTimer(0);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));

    tokenTimer = new QTimer(0);
    tokenTimer->setSingleShot(true);
    connect(tokenTimer, SIGNAL(timeout()), this, SLOT(TokenTimerTimeout()));

    timerTokenMiss = new QTimer(0);
    timer->setSingleShot(true);
    connect(timerTokenMiss, SIGNAL(timeout()), this, SLOT(TokenMiss()));
}

FrameBuilderZR3::~FrameBuilderZR3()
{
    delete timer;
    delete tokenTimer;
    delete timerTokenMiss;
}

void FrameBuilderZR3::ByteReaded(QByteArray ba)
{
    recievedbuf.append(ba);

    if(recievedbuf.size()>1)
    {
        if(recievedbuf.at(0)==(char)(0xFD))
            recievedbuf.insert(0, (char)(0xFF));
    }

    if(recievedbuf.length()>=4)
    {
        int estLength = 0;
        if(recievedbuf.at(2)&0x40)
            estLength = recievedbuf.at(2)&0x3F;
        else
        {
            switch(recievedbuf.at(2)&0x3F)
            {
            case 0x02:
            case 0x03:
            case 0x04:
                estLength = 11;
                break;
            default:
                estLength = 0;
            }
        }

        if(recievedbuf.length()-7>=estLength)
        {
            QMutexLocker locker(&inBufforMutex);
            inBuffor.push_back(Factory::newFrame(recievedbuf.left(7+estLength)));

            timer->stop();
            recievedbuf.remove(0, 7+estLength);
        }
    }

    if((recievedbuf.length()>0)&&(!timer->isActive()))
        timer->start(10);
}

void FrameBuilderZR3::TimeoutedReciev()
{
    emit IgnoredFrame(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}

void FrameBuilderZR3::TokenTimerTimeout()
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(tokenFrame)));
}

void FrameBuilderZR3::TokenMiss()
{
    if(_slowly)
        haveToken = true;
}

void FrameBuilderZR3::FrameWrite(QSharedPointer<Frame> fr)
{
    skipSlowly = true;
    QMutexLocker locker(&outBufforMutex);
    outBuffor.push_back(Factory::newFrame(fr->pureData()));
}

void FrameBuilderZR3::PureDataWrite(QByteArray ba)
{
    skipSlowly = true;
    QByteArray temp;
    temp.push_back(0xFF);
    temp.push_back(0x04);
    temp.push_back(ba.at(0));
    ba.remove(0, 1);
    temp.push_back(_myAdr);
    temp.push_back(ba.size());
    temp.push_back(ba);
    FrameZR3::AppendCRC(temp);
    QMutexLocker locker(&outBufforMutex);
    outBuffor.push_back(Factory::newFrame(temp));
}

void FrameBuilderZR3::ReadInputBuffer()
{
    if(inBuffor.isEmpty())
        return;

    QMutexLocker locker(&inBufforMutex);
    while(!inBuffor.isEmpty())
    {
        QSharedPointer<Frame> frame = QSharedPointer<Frame>(inBuffor.first());
        inBuffor.pop_front();

        if((frame->magicNumbers().at(0)!=(char)0x80))
            skipSlowly = true;

        if((frame->dstAdr().at(0)==(uchar)0x00)||(frame->dstAdr().at(0)==(uchar)0xFF))
        {
            if(frame->magicNumbers().at(0)&0x40)//Data
            {
                emit FrameReaded(frame);
                return;
            }
        }

        if(((uchar)frame->dstAdr().at(0))==_myAdr)
        {
            char val = frame->magicNumbers().at(0);
            if(frame->magicNumbers().at(0)&0x80)
                haveToken = true;


            if(val&0x40)//Data
            {
                emit FrameReaded(frame);
                return;
            }
            emit IgnoredFrame(frame);

            QMutexLocker locker(&outBufforMutex);
            QByteArray temp;
            QByteArray devIDFrame;
            switch(val)
            {
            case (char)0x01://protHELLO
                devIDFrame.append(0xff);
                devIDFrame.append(0xfd);
                devIDFrame.append(0x04);
                devIDFrame.append(frame->srcAdr());
                devIDFrame.append(_myAdr);
                devIDFrame.append(_serial);
                devIDFrame.append((char)(0x01));
                FrameZR3::AppendCRC(devIDFrame);
                outBuffor.push_back(Factory::newFrame(devIDFrame));
                break;
            case(char)0x02://protSET_ADR
                temp = frame->pureData().mid(5, 11);
                if(temp.length()<11)
                    break;
                if(temp.mid(0, 10)!=_serial)
                    break;
                _myAdr = temp.at(10);
                InitTokenFrame();
                break;
            case(char)0x03://protSET_NEXT_ADR
                temp = frame->pureData().mid(5, 11);
                if(temp.length()<11)
                    break;
                if(temp.mid(0, 10)!=_serial)
                    break;
                _nextAdr = temp.at(10);
                InitTokenFrame();
                break;
            case(char)0x04://protDEV_ID
                emit FrameReaded(frame);
                break;
            }
        }
        else
            emit IgnoredFrame(frame);
    }
}

void FrameBuilderZR3::sendOutputBuffer()
{
    if(!haveToken)
        return;

    int timeLeftUs = STANDARD_TOKEN_TIME_MS*1000-BYTE_TIME_US*6;

    while(1)
    {
        QMutexLocker locker(&outBufforMutex);
        if(outBuffor.isEmpty())
            break;
        if(timeLeftUs-outBuffor.first()->pureData().size()*BYTE_TIME_US>0)
        {
            timeLeftUs -= outBuffor.first()->pureData().size()*BYTE_TIME_US;
            emit Write(QSharedPointer<Frame>(outBuffor.first()));
            outBuffor.pop_front();
        }
        else
            break;
    }

    haveToken = false;
    timerTokenMiss->start(2500);
    if(_slowly)
    {
        if(skipSlowly)
        {
            emit Write(QSharedPointer<Frame>(Factory::newFrame(tokenFrame)));
            skipSlowly = false;
        }
        else
            tokenTimer->start(SLOWLY_TOKEN_TIME_MS);
    }
    else
        emit Write(QSharedPointer<Frame>(Factory::newFrame(tokenFrame)));
}

void FrameBuilderZR3::Run()
{
    QThread::msleep(10);
    QCoreApplication::processEvents();
    ReadInputBuffer();
    sendOutputBuffer();
    if(tokenTimer->isActive()&&skipSlowly)
    {
        TokenTimerTimeout();
        tokenTimer->stop();
    }
}
