#include "FrameSProt.hpp"
#include "../Utils/CRC.hpp"
#include "../Utils/StaticUtils.hpp"
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
    validated = true;
    valid = false;
    if( (pck.size()<4) || (pck.size()>64+4))
        return false;

    if(pck.at(0) != 0x5A)
        return false;

    if(CRC::crc8(pck, 0x55, 0xcf, false, false)&0xFF)
        return false;

    valid = true;
    return true;
}

QString FrameSProt::toQString()
{
    if(!isValid())
        return "Invalid pck: " + SU::byteArray2String(pck);
    switch (cmd()) {
    case CMD_HELLO:
        return "Hello";
    case CMD_RHELLO:
        return "ReHello, desc: \""+package()+"\"";
    default:
    {
        return QString("Unknown command, cmd: 0x%1, bytes: %2, data: [ ").arg(cmd(), 3, 16, QChar('0')).arg(bytes())+SU::byteArray2String(package())+"]";
    }
    }
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

uint16_t FrameSProt::cmd()
{
    if(!isValid())
        return 0x1FF;

    return ((pck.at(1)<<1)&0x100) | (pck.at(2)&0xFF);
}

uint8_t FrameSProt::bytes()
{
    if(!isValid())
        return 0;

    return pck.at(1)&0x7F;
}

QByteArray FrameSProt::package()
{
    if(!isValid())
        return QByteArray();

    return pck.mid(3, bytes());
}

QSharedPointer<Frame> FrameSProt::hello()
{
    return QSharedPointer<Frame>(new FrameSProt(CMD_HELLO));
}
