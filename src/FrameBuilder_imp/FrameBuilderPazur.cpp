#include "FrameBuilderPazur.hpp"
#include "../Factory.hpp"
#include <QTimer>
#include <QDebug>
#include <cassert>
#include <stdint.h>
#include <QMutexLocker>
#include "../Utils/CRC.hpp"

FrameBuilderPazur::FrameBuilderPazur():
    FrameBuilder()
{
    Desc::description = "FrameBuilderPazur";

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));
}

FrameBuilderPazur::~FrameBuilderPazur()
{
    delete timer;
}

void FrameBuilderPazur::ByteReaded(QByteArray ba)
{
    timer->start(10);

    QMutexLocker locker(&mutex);
    while(ba.size())
    {
        if(collectingBytes>0)
        {
            potentialFrame.push_back(ba.at(0));
            ba.remove(0, 1);
            if(potentialFrame.size()>=collectingBytes)
            {
                emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(potentialFrame)));
                potentialFrame.clear();
                collectingBytes = 0;
            }
            continue;
        }
        potentialFrame.push_back(ba.at(0));
        ba.remove(0, 1);
        assert(potentialFrame.size()<5);
        if(potentialFrame.size()==4)
        {
            uint8_t crca = (potentialFrame.at(3)>>2)&0x1f;
            uint8_t crcb = CRC::crc5(potentialFrame.mid(0, 3));
            if(crca==crcb)
            {
                if(!trash.isEmpty())
                {
                    emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(trash)));
                    trash.clear();
                }
                collectingBytes = 0;
                collectingBytes |= (potentialFrame.at(2)>>3)&0x1f;
                collectingBytes |= (potentialFrame.at(1)>>2)&0x60;
                collectingBytes += 4 + (potentialFrame.at(2)&0x07)+1;
            }
            else
            {
                trash.push_back(potentialFrame.at(0));
                potentialFrame.remove(0, 1);
                if(trash.size()>10)
                {
                    emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(trash)));
                    trash.clear();
                }
            }
        }
    }
}

void FrameBuilderPazur::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderPazur::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderPazur::Run()
{
    QThread::msleep(4000);
}

void FrameBuilderPazur::TimeoutedReciev()
{
    QMutexLocker locker(&mutex);
    if(!trash.isEmpty())
    {
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(trash)));
        trash.clear();
    }
    if(!potentialFrame.isEmpty())
    {
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(potentialFrame)));
        potentialFrame.clear();
        collectingBytes = 0;
    }
}
