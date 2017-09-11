#include "MendiumRS.hpp"
#include <QString>
#include <QDebug>
#include "../Frame.hpp"

MendiumRS::MendiumRS():
    Mendium()
{
    port.setDataBits(QSerialPort::Data8);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.setStopBits(QSerialPort::OneStop);
    port.setParity(QSerialPort::NoParity);
}

void MendiumRS::Open(QString desc)
{
    qDebug() << "MendiumRS::Open(QString desc)";
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

void MendiumRS::Write(QSharedPointer<Frame> frame)
{
    port.write(frame->pureData());
}

void MendiumRS::Flush()
{

}

void MendiumRS::Close()
{
    port.close();
    opened = false;
    emit Closed();
}

void MendiumRS::Run()
{
    if(port.bytesAvailable())
        emit Readed(port.readAll());
    QThread::msleep(15);
}
