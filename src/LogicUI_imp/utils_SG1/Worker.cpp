#include "Worker.hpp"
#include "../../Factory.hpp"
#include <QDebug>

Worker::Worker(QByteArray dataToSend, int timeout, int repeates):
    EQThread(),
    _dataToSend(dataToSend),
    _repeates(repeates),
    _timeout(timeout)
{
}

Worker::~Worker()
{
}

void Worker::setDataToSend(QByteArray newData)
{
    _dataToSend = newData;
}

void Worker::Run()
{
    if(done)
        return;
    emit SendFrame(_dataToSend);
    QThread::msleep(_timeout);
    if(++counter>=_repeates)
    {
        this->Stop();
        emit Error("Transaction timeouted.");
        emit Fail();
        return;
    }
}

void Worker::RecievedFrame(QByteArray frame)
{
    if(isItOk(frame))
    {
        emit Done(frame);
        done = true;
        this->Stop();
    }
}
