#include "FrameBuilderStawrov.hpp"
#include "../Factory.hpp"

FrameBuilderStawrov::FrameBuilderStawrov()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));
}

FrameBuilderStawrov::~FrameBuilderStawrov()
{
    delete timer;
}

void FrameBuilderStawrov::ByteReaded(QByteArray ba)
{
    timer->stop();
    recievedbuf.append(ba);

    if(recievedbuf.length()>=4)
    {
        if(recievedbuf.length()-6>=recievedbuf.at(3))
        {
            emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf.left(6+recievedbuf.at(3)))));
            recievedbuf.remove(0, 6+recievedbuf.at(3));
        }
    }

    if(recievedbuf.length()>0)
        timer->start(30);
}

void FrameBuilderStawrov::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderStawrov::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderStawrov::Run()
{
    QThread::msleep(4000);
}

void FrameBuilderStawrov::TimeoutedReciev()
{
    emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}
