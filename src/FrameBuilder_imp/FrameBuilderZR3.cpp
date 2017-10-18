#include "FrameBuilderZR3.hpp"
#include "../Factory.hpp"
#include <QDebug>

FrameBuilderZR3::FrameBuilderZR3(uchar myAdr, uchar nextAdr, bool slw):
    _myAdr(myAdr),
    _nextAdr(nextAdr),
    _slowly(slw)
{
    Desc::description = "FrameBuilderZR3";
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
    QThread::msleep(2000);
    QByteArray temp;
    temp.append(_myAdr);
    temp.append(QChar(0x00));
    temp.append(_nextAdr);
    emit Write(QSharedPointer<Frame>(Factory::newFrame(temp)));
    emit IgnoredFrame(QSharedPointer<Frame>(Factory::newFrame(temp)));
}
