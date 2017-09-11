#include "WorkerManager.hpp"
#include <QDebug>

WorkerManager::WorkerManager(QVector<transaction> vec, int maxActiveThreads):
    EQThread(),
    transVec(vec),
    maxThreads(maxActiveThreads)
{

}

WorkerManager::~WorkerManager()
{

}

void WorkerManager::Run()
{
    if(failed+done==transVec.size())
    {
        this->Stop();
        if(failed)
            emit Fail("Nie udało się zrealizować wszystkich transakcji.");
        else
            emit Done();
        return;
    }

    if(((started-done-failed)<maxThreads)&(started<transVec.size()))
    {
        Worker* wk = new Worker(transVec.at(started++));
        connect(this, SIGNAL(InternaFrameCast(QByteArray)), wk, SLOT(RecievedFrame(QByteArray)), Qt::DirectConnection);
        emit InternaFrameCast(QByteArray());
        connect(wk, SIGNAL(SendFrame(QByteArray)), this, SIGNAL(SendFrame(QByteArray)));
        connect(wk, SIGNAL(Done(QByteArray)), this, SLOT(ThreadDone()));
        connect(wk, SIGNAL(Fail()), this, SLOT(ThreadFail()));
        wk->start(QThread::HighPriority);
    }

    QThread::msleep(50);
}

void WorkerManager::RecievedFrame(QByteArray frame)
{
    QByteArray f = frame;
    emit InternaFrameCast(f);
}

void WorkerManager::ThreadDone()
{
    done++;
}

void WorkerManager::ThreadFail()
{
    failed++;
}
