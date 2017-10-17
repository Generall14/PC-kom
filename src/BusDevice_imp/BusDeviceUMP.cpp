#include "BusDeviceUMP.hpp"

BusDeviceUMP::BusDeviceUMP(QByteArray arg):
    BusDevice(arg)
{
    Desc::description = "BusDeviceUMP";
}

void BusDeviceUMP::ByteReaded(QByteArray ba)
{

}

void BusDeviceUMP::Run()
{

}
