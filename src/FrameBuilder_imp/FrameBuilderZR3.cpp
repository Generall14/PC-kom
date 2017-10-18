#include "FrameBuilderZR3.hpp"
#include "../Factory.hpp"
#include <QDebug>

FrameBuilderZR3::FrameBuilderZR3(uchar myAdr, uchar nextAdr, bool slw):
    _myAdr(myAdr),
    _nextAdr(nextAdr),
    _slowly(slw)
{
    Desc::description = "FrameBuilderZR3";

    tokenFrame.append(0xff);
    tokenFrame.append(0x80);
    tokenFrame.append(_nextAdr);
    tokenFrame.append(_myAdr);
    tokenFrame.append(QChar(0x00));
    tokenFrame.append(0xff);

    if(slw)
        haveToken = true;
}

void FrameBuilderZR3::OnStart()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));

    tokenTimer = new QTimer();
    tokenTimer->setSingleShot(true);
    connect(tokenTimer, SIGNAL(timeout()), this, SLOT(TokenTimerTimeout()));
}

FrameBuilderZR3::~FrameBuilderZR3()
{
    delete timer;
    delete tokenTimer;
}

void FrameBuilderZR3::ByteReaded(QByteArray ba)
{
    QMutexLocker locker(&outBufforMutex);
    recievedbuf.append(ba);
    qDebug() << _myAdr << " readed";
}

void FrameBuilderZR3::ReadDataInput()
{
    if(recievedbuf.isEmpty())
        return;

    QMutexLocker locker(&outBufforMutex);

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
    else
        qDebug() << _myAdr << "awiting";

    if((recievedbuf.length()>0)&&(!timer->isActive()))
    {
        qDebug() << _myAdr << " starting timer?";
        timer->start(100);
    }
}

void FrameBuilderZR3::TimeoutedReciev()
{
    qDebug() << _myAdr << " timeouted";
    emit IgnoredFrame(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}

void FrameBuilderZR3::TokenTimerTimeout()
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(tokenFrame)));
}

void FrameBuilderZR3::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderZR3::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
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

        if((uchar)(frame->pureData().at(2))==_myAdr)
        {
            emit FrameReaded(frame);
            if(frame->pureData().at(1)&0x80)
            {
                haveToken = true;
                qDebug() << _myAdr << " get token " << frame->pureData();
            }
        }
        else
        {
            emit IgnoredFrame(frame);
            qDebug() << _myAdr << " not my adress " << frame->pureData();
        }
    }
}

void FrameBuilderZR3::sendOutputBuffer()
{
    if(!haveToken)
        return;

    int timeLeftUs = STANDARD_TOKEN_TIME_MS*1000-BYTE_TIME_US*6;

    while(1)
    {
        if(outBuffor.isEmpty())
            break;
        if(timeLeftUs-outBuffor.first()->pureData().size()*BYTE_TIME_US>0)
        {
            QMutexLocker locker(&outBufforMutex);
            emit Write(QSharedPointer<Frame>(outBuffor.first()));
                qDebug() << _myAdr << " sending " << outBuffor.first()->pureData();
            outBuffor.pop_front();
            timeLeftUs -= outBuffor.first()->pureData().size()*BYTE_TIME_US;
        }
        else
            break;
    }

    haveToken = false;
//    if(_slowly)
//        tokenTimer->start(SLOWLY_TOKEN_TIME_MS);
//    else
        emit Write(QSharedPointer<Frame>(Factory::newFrame(tokenFrame)));
    qDebug() << _myAdr << " sending token " << tokenFrame;
}

void FrameBuilderZR3::Run()
{
    QThread::msleep(1000);
    ReadDataInput();
    ReadInputBuffer();
    sendOutputBuffer();


//    QByteArray temp;
//    temp.append(QChar(_myAdr));
//    emit Write(QSharedPointer<Frame>(Factory::newFrame(temp)));
}
