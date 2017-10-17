#include "MendiumBusConnector.hpp"
#include <QDebug>

MendiumBusConnector::MendiumBusConnector()
{
    Desc::description = "MendiumBusConnector";
}

void MendiumBusConnector::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumBusConnector::Close()
{
    opened = false;
    emit Closed();
}

void MendiumBusConnector::Write(QSharedPointer<Frame>)
{

}

void MendiumBusConnector::Flush()
{

}

void MendiumBusConnector::Run()
{
    QThread::msleep(100);
    if(opened)
    {

    }
}
