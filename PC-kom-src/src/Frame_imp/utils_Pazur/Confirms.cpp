#include "Confirms.hpp"
#include <QDebug>
#include "Utils/CRC.hpp"

Confirms::Confirms()
{
}

Confirms::Confirms(QByteArray dat, uint cnt):
    _dat(dat)
{
    if(cnt==0)
    {
        isEmpty = true;
        return;
    }
    if((uint)dat.size()!=cnt+1)
    {
        isValid = false;
        errorMessage = " Invalid data length";
        return;
    }
    uchar crc = CRC::crc8(dat.mid(0, dat.size()-1));
    if(crc!=(uchar)dat.at(dat.size()-1))
    {
        isValid = false;
        errorMessage = " Invalid crc";
        return;
    }
    for(uint i=0;i<cnt;++i)
        _cfs.push_back(Confirm(dat.at(i)));
    isValid = true;
}

Confirms::Confirms(QList<Confirm> cfs):
    _cfs(cfs)
{
    _dat.clear();
    isValid = true;
    if(cfs.isEmpty())
    {
        isEmpty = true;
        return;
    }

    for(auto a: cfs)
        _dat.append(a.toPureData());
    uchar crc = CRC::crc8(_dat);
    _dat.append(crc);
}

QString Confirms::toQString() const
{
    if(!isEmpty)
    {
        QString temp = "\r\n[Confirms: ";
        if(!isValid)
        {
            temp.append(errorMessage + "\r\n");
            for(auto ch: _dat)
                temp.append(QString("0x%1 ").arg(ch&0xFF, 2, 16, QChar('0')));
        }
        else
        {
            for(auto a: _cfs)
                temp.push_back("\r\n\t( "+a.toQString()+" )");
        }
        temp.append("\r\n]");
        return temp;
    }
    else
        return "";
}

QByteArray Confirms::toPureData() const
{
    return _dat;
}
