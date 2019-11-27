#include "FrameBuilderSProt.hpp"
#include "../Factory.hpp"
#include <QTimer>
#include <QDebug>

uint FrameBuilderSProt::_timeoutMs = 50;
int FrameBuilderSProt::_countTo = 64+4;

FrameBuilderSProt::FrameBuilderSProt():
    FrameBuilder()
{
    Desc::description = "FrameBuilderSProt";

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimeoutedReciev()));
}

FrameBuilderSProt::~FrameBuilderSProt()
{
    delete timer;
}

void FrameBuilderSProt::ByteReaded(QByteArray ba)
{
    if(!timer->isActive())
        timer->start(_timeoutMs);
    recievedbuf.append(ba);

    if(recievedbuf.size()>=2)
    {
        int dsize = (recievedbuf.at(1)&0x7F)+4;
        if(recievedbuf.size()>=dsize)
        {
            QByteArray temp = recievedbuf.left(dsize);
            emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(temp)));
            recievedbuf.remove(0, dsize);

            if(recievedbuf.length()>0)
                timer->start(_timeoutMs);
        }
    }

    while(recievedbuf.length()>=_countTo)
    {
        QByteArray temp = recievedbuf.left(_countTo);
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(temp)));
        recievedbuf.remove(0, _countTo);

        if(recievedbuf.length()>0)
            timer->start(_timeoutMs);
    }
}

void FrameBuilderSProt::FrameWrite(QSharedPointer<Frame> fr)
{
    emit Write(fr);
}

void FrameBuilderSProt::PureDataWrite(QByteArray ba)
{
    emit Write(QSharedPointer<Frame>(Factory::newFrame(ba)));
}

void FrameBuilderSProt::Run()
{
    QThread::msleep(4000);
}

void FrameBuilderSProt::TimeoutedReciev()
{
    if(!recievedbuf.isEmpty())
        emit FrameReaded(QSharedPointer<Frame>(Factory::newFrame(recievedbuf)));
    recievedbuf.clear();
}
