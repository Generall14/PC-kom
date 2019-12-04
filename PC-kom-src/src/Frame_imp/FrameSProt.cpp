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
    case CMD_GETSEC:
    {
        uint16_t offset = package().at(2)<<8 | package().at(1);
        uint8_t num = package().at(0);
        return QString("GetSec, num: 0x%1, offset: 0x%2").arg(num, 2, 16, QChar('0')).arg(offset, 4, 16, QChar('0'));
    }
    case CMD_REGETSEC:
    {
        uint16_t offset = package().at(2)<<8 | package().at(1);
        uint8_t num = package().at(0);
        return QString("ReGetSec, num: 0x%1, offset: 0x%2, data: [").arg(num, 2, 16, QChar('0')).arg(offset, 4, 16, QChar('0'))+SU::byteArray2String(package().mid(3))+"]";
    }
    case CMD_SETSEC:
    {
        uint16_t offset = package().at(2)<<8 | package().at(1);
        uint8_t num = package().at(0);
        return QString("SetSec, num: 0x%1, offset: 0x%2, data: [").arg(num, 2, 16, QChar('0')).arg(offset, 4, 16, QChar('0'))+SU::byteArray2String(package().mid(3))+"]";
    }
    case CMD_RESETSEC:
    {
        QMap<uint8_t, QString> smap = {{0, "Ok"}, {1, "ReadOnly"}, {2, "OutOfRange"}, {3, "UnknownSec"}};
        uint16_t offset = package().at(2)<<8 | package().at(1);
        uint8_t num = package().at(0);
        uint8_t status = package().at(3);
        return QString("ReSetSec, num: 0x%1, offset: 0x%2, status: ").arg(num, 2, 16, QChar('0')).arg(offset, 4, 16, QChar('0'))+smap.value(status, QString::number(status));
    }
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
