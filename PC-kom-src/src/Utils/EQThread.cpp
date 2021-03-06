#include "EQThread.hpp"

EQThread::EQThread(QObject* parent):
    QThread(parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void EQThread::run()
{
    OnStart();
    while(!stopRequest)
    {
        this->Run();
    }
    OnStop();
}

void EQThread::Stop()
{
    stopRequest = true;
}

void EQThread::OnStop()
{

}

void EQThread::OnStart()
{

}
