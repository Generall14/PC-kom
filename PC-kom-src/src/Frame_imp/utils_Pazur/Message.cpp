#include "Message.hpp"
#include "PureMessage.hpp"

Message::Message(const QByteArray& arr):
    _dat(arr)
{
    if(arr.size()<2)
    {
        _isValid = false;
        return;
    }
    _size = arr.at(1)&0x3F;
    _size++;
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

Message::Message(char adr, char ifs, const QByteArray& dat, char x)
{
    _isValid = false;
    if(dat.size()>0x3F)
        return;
    _adr = adr&0x3F;
    _ifs = ifs&0x03;
    _size = dat.size()&0x3F;
    if(_size>0)
        _size--;
    _x = x&0x03;
    _pureDat = dat;
    _isValid = true;

    _dat.append(_adr | ((_ifs<<6)&0xC0));
    _dat.append(_size | ((_x<<6)&0xC0));
    _dat.append(_pureDat);
}

QString Message::toQString() const
{
    QString temp;
    if(!_isValid)
    {
        temp.append("Invalid message: ");
        for(auto a: _dat)
            temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
    }
    else
    {
        temp.append(QString("adr: 0x%1, size: 0x%2, if: ").arg((uint)_adr&0xFF, 2, 16, QChar('0')).arg((uint)_size&0xFF, 2, 16, QChar('0')));
        temp.append(QString::number(_ifs)+", x: "+QString::number(_x)+". ");
        temp.append(PureMessage(_dat).desc());
    }
    return temp;
}

QByteArray Message::toPureData() const
{
    return _dat;
}

void Message::get(char &adr, char &ifs, QByteArray &dat, char &x) const
{
    adr = _adr;
    ifs = _ifs;
    dat = _pureDat;
    x = _x;
}
