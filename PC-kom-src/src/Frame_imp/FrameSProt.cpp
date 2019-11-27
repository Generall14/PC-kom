#include "FrameSProt.hpp"
#include "../Utils/CRC.hpp"
#include <qdebug.h>

FrameSProt::FrameSProt(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameSProt";
}


FrameSProt::FrameSProt(uint16_t cmd, QByteArray data):
    FrameSProt(QByteArray())
{
    if(data.size()<=64)
    {
        pck.append(0x5A);
        pck.append( (data.size()&0x7F) | ((cmd>>1)&0x80) );
        pck.append(cmd&0xFF);
        pck.append(data);
        pck.append(CRC::crc8(pck, 0x55, 0xcf, false, false)&0xFF);
    }
}

bool FrameSProt::isValid()
{
    return true;
}

QString FrameSProt::toQString()
{
    qDebug() << CRC::crc8(pck, 0x55, 0xcf, false, false);
    return "Nic tu nie ma - to tylko testowa implementacja klasy Frame";
}

QString FrameSProt::toShortQString()
{
    return "XXX";
}

QByteArray FrameSProt::magicNumbers()
{
    return "XXX";
}
