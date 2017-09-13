#include "Worker.hpp"
#include "../../Factory.hpp"
#include <QDebug>

Worker::Worker(transaction req):
    EQThread(),
    transactionRequest(req)
{
}

Worker::~Worker()
{
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

void Worker::RecievedFrame(QByteArray frame)
{
    QSharedPointer<Frame> temp = QSharedPointer<Frame>(Factory::newFrame(frame));
    if(temp->magicNumbers()==transactionRequest.requestedMagisNumber)
    {
        emit Done(frame);
        done = true;
        this->Stop();
    }
}
