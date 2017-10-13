#include "FrameBuilderEmpty.hpp"
#include "../Factory.hpp"

FrameBuilderEmpty::FrameBuilderEmpty()
{

}

void FrameBuilderEmpty::ByteReaded(QByteArray ba)
{
    QSharedPointer<Frame> fr = QSharedPointer<Frame>(Factory::newFrame(ba));
    emit FrameReaded(fr);
}

void FrameBuilderEmpty::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderEmpty::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderEmpty::Run()
{
    QThread::msleep(4000);
}
