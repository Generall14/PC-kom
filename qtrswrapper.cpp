#include "qtrswrapper.h"

QtRSWrapper::QtRSWrapper()
{
    port.setBaudRate(QSerialPort::Baud19200);
    port.setDataBits(QSerialPort::Data8);
    port.setFlowControl(QSerialPort::NoFlowControl);
    port.setStopBits(QSerialPort::OneStop);
    timer.setSingleShot(true);
}

void QtRSWrapper::run()
{
    while(!stopRequest)
    {
        timer.start(666);
        while(timer.isActive())
        {
            if(port.bytesAvailable()>=5)
            {
                emit Readed(port.read(5));
                continue;
            }
        }
        if((port.bytesAvailable()<5)&&(port.bytesAvailable()>0))
            emit Readed(port.readAll());
    }
    Close();
}

void QtRSWrapper::Stop()
{
    stopRequest = true;
}

void QtRSWrapper::Open(QString portname)
{
    if(!opened)
    {
        port.setPortName(portname);
        if(port.open(QIODevice::ReadWrite))
        {
            opened = true;
            emit Opened();
            return;
        }
        opened = false;
        emit Error("ERROR! Nie można otworzyć portu "+portname+"!");
        emit Closed();
    }
}

void QtRSWrapper::Close()
{
    port.close();
    opened = false;
    emit Closed();
}
