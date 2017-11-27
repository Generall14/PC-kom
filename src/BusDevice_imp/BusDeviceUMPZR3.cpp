#include "BusDeviceUMPZR3.hpp"

BusDeviceUMPZR3::BusDeviceUMPZR3(QString arg):
    BusDeviceUMP(arg)
{
    Desc::description = "BusDeviceUMPZR3";
}

void BusDeviceUMPZR3::OnRun()
{

}

QByteArray BusDeviceUMPZR3::OnDataRecieved(QByteArray data)
{
    QByteArray toWrite;
    uchar val = data.at(0);
    switch(val)
    {
    case (uchar)0x20:
        toWrite.append(0xa0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        break;
    case (uchar)0x22:
        toWrite.append(0xa2);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        toWrite.append(0xe0);
        break;
    default:
        return toWrite;
    }
    return toWrite;
}
