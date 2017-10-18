#include "MendiumBusConnector.hpp"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "../Factory.hpp"

MendiumBusConnector::MendiumBusConnector()
{
    Desc::description = "MendiumBusConnector";
}

void MendiumBusConnector::OnStart()
{
    QFile config1File("inputs/MendiumBusConnectorIn.cfg");
    if(!config1File.open(QIODevice::Text | QIODevice::ReadOnly))
        emit Error("Nie można odczytać pliku konfiguracyjnego \"inputs/MendiumBusConnectorIn.cfg\"");
    else
    {
        QTextStream in(&config1File);
        while(!in.atEnd())
        {
            BusDevice* temp = Factory::newBusDevice(in.readLine());
            devicesVector.push_back(temp);
            connect(temp, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
            connect(temp, &BusDevice::Write, [=](QByteArray ba){emit Readed(ba);});
            connect(this, SIGNAL(HALT()), temp, SLOT(Stop()));
            connect(this, &MendiumBusConnector::Readed, temp, &BusDevice::ByteReaded);
            temp->start(QThread::NormalPriority);
        }
        config1File.close();
    }
}

void MendiumBusConnector::OnStop()
{
    emit HALT();
    for(BusDevice* temp: devicesVector)
    {
        while(temp->isRunning()){}
        delete temp;
    }
    devicesVector.clear();
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

void MendiumBusConnector::Write(QSharedPointer<Frame> fr)
{
    QMutexLocker locker(&mutex);
//    emit Readed(fr->pureData());
    gtemp.append(fr->pureData());

}

void MendiumBusConnector::Flush()
{

}

void MendiumBusConnector::Run()
{
    QThread::msleep(10);
    if(!gtemp.isEmpty())
    {
        QMutexLocker locker(&mutex);
        emit Readed(gtemp);
        gtemp.clear();
    }
    if(opened)
    {

    }
}
