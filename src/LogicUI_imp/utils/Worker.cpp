#include "Worker.hpp"
#include <QDebug>

Worker::Worker(transaction req):
    EQThread(),
    transactionRequest(req)
{
    qDebug() << "konstruntor worker";
}

Worker::~Worker()
{
    qDebug() << "destruktor worker";
}

void Worker::Run()
{
    if(done)
        return;
    emit SendFrame(transactionRequest.sendFrame->pureData());
    QThread::msleep(transactionRequest.timeout);
    if(++counter>=transactionRequest.maxrepeate)
    {
        this->Stop();
        emit Error("Transaction timeouted.");
        emit Fail();
        return;
    }
}

void Worker::RecievedFrame(QSharedPointer<Frame> frame)
{
    if(frame->magicNumbers()==transactionRequest.requestedMagisNumber)
    {
        emit Done(frame);
        done = true;
        this->Stop();
    }
}
