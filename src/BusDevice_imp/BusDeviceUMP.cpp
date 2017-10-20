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
    if(data.size()<6)
    {
        emit Error("Błąd parsowania adresów pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    else
    {
        myADr = data.at(0);
        nextAdr = data.at(1);
    }

    int stptr = 0, stsize = 0;
    stptr |= (data.at(2)<<8)&0xFF00;
    stptr |= (data.at(3)<<0)&0x00FF;
    stsize |= (data.at(4)<<8)&0xFF00;
    stsize |= (data.at(5)<<0)&0x00FF;
    if(data.length()<stptr+stsize-1)
    {
        emit Error("Błąd parsowania listy stringów pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    stringTable = data.mid(stptr, stsize);

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
