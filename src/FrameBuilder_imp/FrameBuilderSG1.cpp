#include "FrameBuilderSG1.hpp"
#include "../Factory.hpp"
#include <QTimer>
#include <QDebug>

FrameBuilderSG1::FrameBuilderSG1():
    FrameBuilder()
{
    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));
}

FrameBuilderSG1::~FrameBuilderSG1()
{
    delete timer;
}

void FrameBuilderSG1::ByteReaded(QByteArray ba)
{
    timer->stop();
    recievedbuf.append(ba);

    while(recievedbuf.length()>=5)
    {
        QByteArray temp = recievedbuf.left(5);
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(temp)));
        recievedbuf.remove(0, 5);
    }

    if(recievedbuf.length()>0)
        timer->start(666);
}

void FrameBuilderSG1::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderSG1::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderSG1::Run()
{
    QThread::msleep(4000);
}

void FrameBuilderSG1::TimeoutedReciev()
{
    emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}
