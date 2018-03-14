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

FramePazur::FramePazur(uchar from, uchar to, uchar id, bool fast, QList<Confirm> cfs, QList<Message> msgs, bool kwitowanie):
    Frame(QByteArray()),
    _from(from),
    _to(to),
    _id(id),
    _fast(fast)
{
    Desc::description = "FramePazur";
    isItOk = true;
    _cfs = Confirms(cfs);
    _confs = cfs.size();
    _msgs = Messages(msgs, id);
    _dataSize = _msgs.toPureData().size();
    if(_dataSize<=1)
    {
        if(kwitowanie)
            _dataSize = 1;
        else
            _dataSize = 0;
    }
    _crc10add = _msgs.addCrc10();

    pck.clear();
    char temp = 0x00;
    temp |= _from&0x3F;
    temp |= (_id<<7)&0x80;
    if(_fast)
        temp |= 0x40;
    pck.append(temp);

    temp = 0x00;
    temp |= _to&0x3F;
    temp |= (_dataSize<<1)&0xC0;
    pck.append(temp);

    temp = 0x00;
    temp |= _confs&0x07;
    temp |= (_dataSize<<3)&0xF8;
    pck.append(temp);

    temp = 0x00;
    uchar crc5 = CRC::crc5(pck.mid(0, 3));
    temp |= (crc5<<2)&0x7C;
    temp |= _crc10add&0x03;
    temp |= (_id<<6)&0x80;
    pck.append(temp);

    pck.append(_cfs.toPureData());
    if(_dataSize>1)
        pck.append(_msgs.toPureData());
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
        temp.append("");
        temp.append(dispHeader());
        temp.append(_cfs.toQString());
        temp.append(_msgs.toQString());
        temp.append("\n\n");
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
    uint8_t crca = ((pck.at(3)&0x7C)>>2);
    uint8_t crcb = CRC::crc5(pck.mid(0, 3))&0x1F;
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

    _cfs = Confirms(pck.mid(4, _confs+1), _confs);
    if(_confs)
        _msgs = Messages(pck.mid(4+_confs+1), _dataSize, _crc10add, _id);
    else
        _msgs = Messages(pck.mid(4), _dataSize, _crc10add, _id);
}

QString FramePazur::dispHeader()
{
    QString temp = "[";
    temp.append(QString("0x%1->0x%2").arg(_from, 2, 16, QChar('0')).arg(_to, 2, 16, QChar('0')));
    temp.append(", conf: " + QString::number(_confs) + ", dat: ");
    if(_dataSize==0xFF)
        temp.append("0");
    else if(_dataSize==0x00)
        temp.append("K");
    else
        temp.append(QString::number(_dataSize));
    temp.append(", F: " + QString::number(_fast) + ", ID: " + QString::number(_id) + ", sl: " + QString::number(_crc10add) + "] ");
    return temp;
}
