#include "MendiumRS.hpp"
#include <QString>

MendiumRS::MendiumRS():
    Mendium()
{
    timer.setSingleShot(true);
    port.setDataBits(QSerialPort::Data8);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.setStopBits(QSerialPort::OneStop);
}

void MendiumRS::Open(QString desc)
{
    if(!opened)
    {
        QStringList params = desc.split(";");
        if(params.length()<2)
        {
            opened = false;
            emit Error("ERROR! Nie można otworzyć portu "+desc+"!");
            emit Closed();
        }
        port.setPortName(params.at(0));
        port.setBaudRate(QString(params.at(1)).toInt());
        if(port.open(QIODevice::ReadWrite))
        {
            opened = true;
            emit Opened();
            return;
        }
        opened = false;
        emit Error("ERROR! Nie można otworzyć portu "+desc+"!");
        emit Closed();
    }
}

void MendiumRS::Close()
{
    port.close();
    opened = false;
    emit Closed();
}

void MendiumRS::Run()
{
    timer.start(readTimeout);
    while(timer.isActive())
    {
        if(port.bytesAvailable()>=frameLength)
        {
            emit Readed(port.read(frameLength));
            continue;
        }
    }
    if((port.bytesAvailable()<frameLength)&&(port.bytesAvailable()>0))
        emit Readed(port.readAll());
}
