#include "FrameBuilderZR3.hpp"
#include "../Factory.hpp"

FrameBuilderZR3::FrameBuilderZR3()
{

}

void FrameBuilderZR3::ByteReaded(QByteArray ba)
{
    QSharedPointer<Frame> fr = QSharedPointer<Frame>(Factory::newFrame(ba));
    emit FrameReaded(fr);
}

void FrameBuilderZR3::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderZR3::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderZR3::Run()
{
    QThread::msleep(4000);
}
