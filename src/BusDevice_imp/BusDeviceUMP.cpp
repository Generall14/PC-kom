#include "BusDeviceUMP.hpp"
#include <QDebug>

BusDeviceUMP::BusDeviceUMP(QString arg):
    BusDevice(arg)
{
    Desc::description = "BusDeviceUMP";
}

void BusDeviceUMP::ByteReaded(QByteArray ba)
{

}

void BusDeviceUMP::Run()
{
    QThread::msleep(2000);
}

void BusDeviceUMP::OnStart()
{
    qDebug() << "on start" + QString(_arg);
}

void BusDeviceUMP::OnStop()
{
    qDebug() << "on stop" + QString(_arg);
}
