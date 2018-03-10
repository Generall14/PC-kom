#include "Confirm.hpp"

Confirm::Confirm(char dat):
    _dat(dat)
{
    _adr = dat&0x3F;
    _id = (dat&0xC0)>>6;
}

Confirm::Confirm(char adr, char id)
{
    char x = 0x00;
    x |= adr&0x3f;
    x |= (id<<6)&0xC0;
    _dat = x;
}

QString Confirm::toQString() const
{
    return QString("adr: 0x%1, id: ").arg((int)_adr, 2, 16, QChar('0'))+QString::number(_id);
}

QChar Confirm::toPureData() const
{
    return _dat;
}
