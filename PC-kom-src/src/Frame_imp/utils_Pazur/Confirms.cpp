#include "Confirms.hpp"
#include <QDebug>

Confirms::Confirms()
{
}

Confirms::Confirms(QByteArray dat, int cnt):
    _dat(dat)
{
    if(dat.size()!=cnt+1)
    {
        isValid = false;
        errorMessage = " Invalid data length";
        return;
    }
    // crc...
    for(int i=0;i<cnt;++i)
        _cfs.push_back(Confirm(dat.at(i)));
    isValid = true;
}

Confirms::Confirms(QList<Confirm> cfs):
    _cfs(cfs)
{
    if(cfs.isEmpty())
        isEmpty = true;
    isValid = true;

    for(auto a: cfs)
        _dat.append(a.toPureData());
    _dat.append(0xFF);//crc...
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
                temp.append(QString("0x%1 ").arg(ch, 2, 16, QChar('0')));
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
