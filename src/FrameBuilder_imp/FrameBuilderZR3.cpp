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

    InitTokenFrame();

    if(slw)
        haveToken = true;
}

void FrameBuilderZR3::InitTokenFrame()
{
    tokenFrame.clear();
    tokenFrame.append(0xff);
    tokenFrame.append(0x80);
    tokenFrame.append(_nextAdr);
    tokenFrame.append(_myAdr);
    tokenFrame.append(QChar(0x00));
    FrameZR3::AppendLRC(tokenFrame);
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

    if(recievedbuf.length()>=5)
    {
        if(recievedbuf.length()-6>=recievedbuf.at(4))
        {
            QMutexLocker locker(&inBufforMutex);
            inBuffor.push_back(Factory::newFrame(recievedbuf.left(6+recievedbuf.at(4))));

            timer->stop();
            recievedbuf.remove(0, 6+recievedbuf.at(4));
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
    FrameZR3::AppendLRC(temp);
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

        if((frame->pureData().at(1)&0x1f)!=0x00)
            skipSlowly = true;

        if((uchar)(frame->pureData().at(2))==_myAdr)
        {
//            emit FrameReaded(frame);
            char val = frame->pureData().at(1)&0x1f;
            if(frame->pureData().at(1)&0x80)
                haveToken = true;

            if(val==(char)0x04)//Data
            {
                emit FrameReaded(frame);
                return;
            }
            emit IgnoredFrame(frame);

            QMutexLocker locker(&outBufforMutex);
            QByteArray temp;
            switch(val)
            {
            case (char)0x01://protHELLO
                temp.push_back(0xFF);
                temp.push_back((char)0x00);
                temp.push_back(frame->pureData().at(3));
                temp.push_back(_myAdr);
                temp.push_back((char)0x00);
                FrameZR3::AppendLRC(temp);
                outBuffor.push_back(Factory::newFrame(temp));
                break;
            case(char)0x02://protSET_ADR
                _myAdr = frame->pureData().at(5);
                InitTokenFrame();
                break;
            case(char)0x03://protSET_NEXT_ADR
                _nextAdr = frame->pureData().at(5);
                InitTokenFrame();
                break;
//            case (char)0x04://Data
//                emit FrameReaded(frame);
//                break;
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
