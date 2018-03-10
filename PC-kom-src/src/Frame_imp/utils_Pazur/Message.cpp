#include "Message.hpp"

Message::Message(QByteArray arr):
    _dat(arr)
{
    if(arr.size()<3)
    {
        _isValid = false;
        return;
    }
    _size = arr.at(1)&0x3F;
    if(arr.size()!=_size+2)
    {
        _isValid = false;
        return;
    }
    _adr = arr.at(0)&0x3F;
    _ifs = (arr.at(0)&0xC0)>>6;
    _x = (arr.at(1)&0xC0)>>6;
    _isValid = true;
}

Message::Message(char adr, char ifs, QByteArray dat, char x)
{
    if(dat.size()>0x3F)
        return;
    if(dat.isEmpty())
        return;
    _dat.append((adr&0x3F) || ((ifs)&0xC0));
    _dat.append((dat.size()&0x3F) || ((x)&0xC0));
    _dat.append(dat);
}

QString Message::toQString() const
{
    QString temp;
    if(!_isValid)
    {
        temp.append("Invalid message: ");
        for(auto a: _dat)
            temp.append(QString("0x%1 ").arg(a, 2, 16, QChar('0')));
    }
    else
    {
        temp.append(QString("adr: 0x%1, size: 0x%2, if: ").arg(_adr, 2, 16, QChar('0')).arg(_size, 2, 16, QChar('0')));
        temp.append(QString::number(_ifs)+", x: "+QString::number(_x)+". ");
        temp.append("Data: ");
        for(int i =2;i<_dat.size();++i)
            temp.append(QString("0x%1 ").arg(_dat.at(i), 2, 16, QChar('0')));
    }
    return temp;
}

QByteArray Message::toPureData() const
{
    return _dat;
}
