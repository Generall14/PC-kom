#include "EQThread.hpp"

EQThread::EQThread(QObject* parent):
    QThread(parent)
{
    connect(this, SIGNAL(finished()), this, SLOT(deleteLater()));
}

void EQThread::run()
{
    while(!stopRequest)
    {
        this->Run();
    }
}

void EQThread::Stop()
{
    stopRequest = true;
}
