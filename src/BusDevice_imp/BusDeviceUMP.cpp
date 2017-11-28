#include "BusDeviceUMP.hpp"
#include <QDebug>
#include <QFile>
#include <QCoreApplication>
#include <QtGlobal>

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
    QThread::msleep(TIME_STEP_MS);
    OnRun();
    QCoreApplication::processEvents();
}

void BusDeviceUMP::OnStart()
{
    QFile config1File(_arg);
    if(!config1File.open(QIODevice::ReadOnly))
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
        emit Error("Błąd parsowania adresów pliku z konfiguracyjnego \"" + _arg + "\"");
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
    if((data.length()<stptr+stsize-1)||(stptr<=1))
    {
        emit Error("Błąd parsowania listy stringów z pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    stringTable = data.mid(stptr, stsize);

    stptr = 0;
    stsize = 0;
    stptr |= (data.at(6)<<8)&0xFF00;
    stptr |= (data.at(7)<<0)&0x00FF;
    stsize |= (data.at(8)<<8)&0xFF00;
    stsize |= (data.at(9)<<0)&0x00FF;
    if((data.length()<stptr+stsize-1)||(stptr<=1))
    {
        emit Error("Błąd parsowania deskryptora urządzenia z pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    deviceDescriptor = data.mid(stptr, stsize);

    stptr = 0;
    stsize = 0;
    stptr |= (data.at(10)<<8)&0xFF00;
    stptr |= (data.at(11)<<0)&0x00FF;
    stsize |= (data.at(12)<<8)&0xFF00;
    stsize |= (data.at(13)<<0)&0x00FF;
    if((data.length()<stptr+stsize-1)||(stptr<=1))
    {
        emit Error("Błąd parsowania deskryptora metod z pliku konfiguracyjnego \"" + _arg + "\"");
        return;
    }
    methodsDescriptor = data.mid(stptr, stsize);

    frameBuilder = new FrameBuilderZR3(myADr, nextAdr, false);
    connect(this, SIGNAL(toFrameByteReaded(QByteArray)), frameBuilder, SLOT(ByteReaded(QByteArray)));
    connect(this, SIGNAL(Halt()), frameBuilder, SLOT(Stop()));
    connect(this, SIGNAL(AplWritePureData(QByteArray)), frameBuilder, SLOT(PureDataWrite(QByteArray)));
    connect(frameBuilder, &FrameBuilderZR3::Write, [=](QSharedPointer<Frame> fr){emit Write(fr->pureData());});
    connect(frameBuilder, SIGNAL(FrameReaded(QSharedPointer<Frame>)), this, SLOT(AplFrameReaded(QSharedPointer<Frame>)));
    frameBuilder->start(QThread::NormalPriority);
}

QByteArray BusDeviceUMP::GetFileData(QByteArray& ba, uint16_t ptr, uint8_t size)
{
    QByteArray temp;
    if(ptr>=ba.size())
        return temp;
    if(size==0)
        return temp;
    if(MAX_DATA_FILE_SIZE<size)
        size = MAX_DATA_FILE_SIZE;
    temp.append(ba.mid(ptr, size));
    return temp;
}

void BusDeviceUMP::OnStop()
{
    emit Halt();
    if(frameBuilder)
    {
        while(frameBuilder->isRunning()){}
    }
}

void BusDeviceUMP::AplFrameReaded(QSharedPointer<Frame> fr)
{
    QByteArray data = fr->pureData().mid(5, fr->pureData().at(4));
    uchar val = data.at(0);

    if((val==(uchar)0x0A)||(val==(uchar)0x01)||(val==(uchar)0x09))
    {
        QByteArray toWrite;
        toWrite.append(fr->pureData().at(3));
        uint16_t off = 0;
        if(data.size()<3)
            return;
        off |= (data.at(1)<<8)&0xFF00;
        off |= (data.at(2)<<0)&0x00FF;
        uint8_t siz = data.at(3);
        switch(val)
        {
        case (uchar)0x0A:
            toWrite.append(0x8A);
            toWrite.append(GetFileData(stringTable, off, siz));
            break;
        case (uchar)0x01:
            toWrite.append(0x81);
            toWrite.append(GetFileData(deviceDescriptor, off, siz));
            break;
        case (uchar)0x09:
            toWrite.append(0x89);
            toWrite.append(GetFileData(methodsDescriptor, off, siz));
            break;
        default:
            return;
        }

        emit AplWritePureData(toWrite);
        return;
    }
    else
    {
        QByteArray toWrite = OnDataRecieved(data);
        if(!toWrite.isEmpty())
        {
            toWrite.insert(0, fr->pureData().at(3));
            emit AplWritePureData(toWrite);
        }
        return;
    }
}

void BusDeviceUMP::OnRun()
{

}

QByteArray BusDeviceUMP::OnDataRecieved(QByteArray data)
{

}
