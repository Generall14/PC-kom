#include "FramePazur.hpp"
#include "../Utils/CRC.hpp"
#include <stdint.h>
#include <assert.h>

FramePazur::FramePazur(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FramePazur";
}

bool FramePazur::isValid()
{
    if(!isHeaderOk())
        return false;
    return true;
}

QString FramePazur::toQString()
{
    QString temp;

    if(isHeaderOk())
    {
        temp.append(dispHeader());
        for(int i=4;i<pck.size();++i)
            temp.append(QString("0x%1 ").arg(((int)(pck.at(i)))&0xFF, 2, 16, QChar('0')));
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

QString FramePazur::dispHeader()
{
    assert(pck.size()>=4);
    QString temp = "[";
    temp.append(QString("0x%1->0x%2").arg(((int)(pck.at(0)))&0x3F, 2, 16, QChar('0')).arg(((int)(pck.at(1)))&0x3F, 2, 16, QChar('0')));
    int dat = 0;
    dat |= (pck.at(2)>>3)&0x1f;
    dat |= (pck.at(1)>>2)&0x60;
    dat -= 1;
    int conf = pck.at(2)&0x07;
    temp.append(", conf: " + QString::number(conf) + ", dat: " + QString::number(dat));
    int f = 0, id = 0, sl = 0;
    f = (pck.at(0)>>6)&0x01;
    sl = pck.at(3)&0x03;
    id |= (pck.at(0)>>7)&0x01;
    id |= (pck.at(3)>>6)&0x02;
    temp.append(", F: " + QString::number(f) + ", ID: " + QString::number(id) + ", sl: " + QString::number(sl) + "]");
    return temp;
}
