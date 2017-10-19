#include "BusDeviceUMP.hpp"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

BusDeviceUMP::BusDeviceUMP(QString arg):
    BusDevice(arg)
{
    Desc::description = "BusDeviceUMP";
}

void BusDeviceUMP::ByteReaded(QByteArray ba)
{
    emit toFrameByteReaded(ba);
}

void BusDeviceUMP::Run()
{
    QThread::msleep(10);
    QCoreApplication::processEvents();
}

void BusDeviceUMP::OnStart()
{
    QFile config1File(_arg);
    if(!config1File.open(QIODevice::Text | QIODevice::ReadOnly))
        emit Error("Nie można odczytać pliku konfiguracyjnego \"" + _arg + "\"");
    else
    {
        ParseConfigFile(config1File.readAll());
        config1File.close();
    }
}

void BusDeviceUMP::ParseConfigFile(QByteArray data)
{
    if(data.size()<2)
    {
        emit Error("Błąd parsowania adresów pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    else
    {
        myADr = data.at(0);
        nextAdr = data.at(1);
        data.remove(0, 2);
    }

    frameBuilder = new FrameBuilderZR3(myADr, nextAdr, false);
    connect(this, SIGNAL(toFrameByteReaded(QByteArray)), frameBuilder, SLOT(ByteReaded(QByteArray)));
    connect(this, SIGNAL(Halt()), frameBuilder, SLOT(Stop()));
    connect(frameBuilder, &FrameBuilderZR3::Write, [=](QSharedPointer<Frame> fr){emit Write(fr->pureData());});
    frameBuilder->start(QThread::NormalPriority);
}

void BusDeviceUMP::OnStop()
{
    emit Halt();
    if(frameBuilder)
    {
        while(frameBuilder->isRunning()){}
    }
}
