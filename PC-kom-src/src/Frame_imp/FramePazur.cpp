#include "FramePazur.hpp"
#include "../Utils/CRC.hpp"
#include <stdint.h>
#include <assert.h>
#include <QDebug>

FramePazur::FramePazur(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FramePazur";

    if(isHeaderOk())
    {
        isItOk = true;
        parse();
    }
}

bool FramePazur::isValid()
{
    return isItOk;
}

QString FramePazur::toQString()
{
    QString temp;

    if(isItOk)
    {
        temp.append("\r\n");
        temp.append(dispHeader());
        temp.append(_cfs.toQString());
        temp.append(_msgs.toQString());
        temp.append("\r\n\r\n\r\n");
    }
    else
    {
        for(auto s: pck)
            temp.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
        temp.remove(temp.size()-1, 1);
        temp = temp.toUpper();
        temp = temp.replace("X", "x");
    }

    return temp;
}

QString FramePazur::toShortQString()
{
    return "XXX";
}

QByteArray FramePazur::magicNumbers()
{
    return "XXX";
}

bool FramePazur::isHeaderOk()
{
    if(pck.size()<4)
        return false;
    uint8_t crca = (pck.at(3)>>2)&0x1f;
    uint8_t crcb = CRC::crc5(pck.mid(0, 3));
    if(crca!=crcb)
        return false;
    return true;
}

void FramePazur::parse()
{
    assert(pck.size()>=4);

    // dane naglowka:
    _from = (int)pck.at(0)&0x3F;

    _to = (int)pck.at(1)&0x3F;

    _dataSize = 0;
    _dataSize |= (pck.at(2)>>3)&0x1f;
    _dataSize |= (pck.at(1)>>2)&0x60;
    _dataSize -= 1;

    _confs = pck.at(2)&0x07;

    _fast = (pck.at(0)>>6)&0x01;

    _crc10add = pck.at(3)&0x03;

    _id = 0;
    _id |= (pck.at(0)>>7)&0x01;
    _id |= (pck.at(3)>>6)&0x02;

    // Potwierdzenia:
    _cfs = Confirms(pck.mid(4, _confs+1), _confs);
    _msgs = Messages(pck.mid(4+_confs+1), _dataSize, _crc10add);
}

QString FramePazur::dispHeader()
{
    QString temp = "[";
    temp.append(QString("0x%1->0x%2").arg(_from, 2, 16, QChar('0')).arg(_to, 2, 16, QChar('0')));
    temp.append(", conf: " + QString::number(_confs) + ", dat: " + QString::number(_dataSize));
    temp.append(", F: " + QString::number(_fast) + ", ID: " + QString::number(_id) + ", sl: " + QString::number(_crc10add) + "] ");
    return temp;
}
