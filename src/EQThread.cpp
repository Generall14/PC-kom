#include "EQThread.hpp"

EQThread::EQThread(QObject* parent):
    QThread(parent)
{

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
