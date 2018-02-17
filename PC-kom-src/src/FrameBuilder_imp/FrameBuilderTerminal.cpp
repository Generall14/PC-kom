#include "FrameBuilderTerminal.hpp"
#include "../Factory.hpp"
#include <QTimer>
#include <QDebug>

uint FrameBuilderTerminal::_timeoutMs = 100;
uint FrameBuilderTerminal::_countTo = 10;

FrameBuilderTerminal::FrameBuilderTerminal():
    FrameBuilder()
{
    Desc::description = "FrameBuilderTerminal";

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));
}

FrameBuilderTerminal::~FrameBuilderTerminal()
{
    delete timer;
}

void FrameBuilderTerminal::ByteReaded(QByteArray ba)
{
    if(!timer->isActive())
        timer->start(getTimeoutMs());
    recievedbuf.append(ba);

    int size = getPckSize();

    while(recievedbuf.length()>=size)
    {
        QByteArray temp = recievedbuf.left(size);
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(temp)));
        recievedbuf.remove(0, size);

        if(recievedbuf.length()>0)
            timer->start(getTimeoutMs());
    }
}

void FrameBuilderTerminal::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderTerminal::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderTerminal::Run()
{
    QThread::msleep(4000);
}

void FrameBuilderTerminal::TimeoutedReciev()
{
    if(!recievedbuf.isEmpty())
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}

uint FrameBuilderTerminal::getTimeoutMs()
{
    return _timeoutMs;
}

uint FrameBuilderTerminal::getPckSize()
{
    return _countTo;
}

void FrameBuilderTerminal::setTimeoutMs(uint val)
{
    _timeoutMs = val;
}

void FrameBuilderTerminal::setPckSize(uint val)
{
    _countTo = val;
}
