#include "FrameBuilderStawrov.hpp"
#include "../Factory.hpp"

FrameBuilderStawrov::FrameBuilderStawrov()
{
    Desc::description = "FrameBuilderStawrov";

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

    if(recievedbuf.length()>=3)
    {
        if(recievedbuf.length()-5>=recievedbuf.at(2))
        {
            emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf.left(5+recievedbuf.at(2)))));
            recievedbuf.remove(0, 5+recievedbuf.at(2));
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
