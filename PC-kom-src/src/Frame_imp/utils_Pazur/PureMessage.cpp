#include "PureMessage.hpp"
#include <cassert>
#include <qDebug>

PureMessage::PureMessage(QByteArray arr):
    _arr(arr)
{
    assert(arr.size()>=2);
}

QString PureMessage::desc() const
{
    QString temp = " [";
    uchar inf = (_arr.at(0)>>6)&0x03;
    bool done = false;

    switch (inf)
    {
    case 0b00:
        break;
    case 0b01:
    {
        uchar code01 = _arr.at(2)&0x0F;
        switch (code01)
        {
        case wiRDCONST_c:
        {
            if(_arr.size()!=5)
                break;
            uint off = 0;
            off |= _arr.at(3)&0xFF;
            off |= (_arr.at(4)<<8)&0xFF00;
            off |= (_arr.at(2)<<12)&0xF0000;
            temp.append(QString("wiRDCONST, offset: 0x%1").arg(off, 5, 16, QChar('0')));
            done = true;
            break;
        }
        case wiRDCONSTo_c:
        {
            if(_arr.size()<5)
                break;
            uint off = 0;
            off |= _arr.at(3)&0xFF;
            off |= (_arr.at(4)<<8)&0xFF00;
            off |= (_arr.at(2)<<12)&0xF0000;
            temp.append(QString("wiRDCONSTo, offset: 0x%1, data:").arg(off, 5, 16, QChar('0')));
            for(int i=5;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            break;
        }
        case wiRDSECTION_c:
        {
            if(_arr.size()<4)
                break;
            QByteArray xxx;
            for(int i=0;i<5;++i)
            {
                if(3+i>=_arr.size())
                    break;
                xxx.append(_arr.at(3+i));
                if(!(_arr.at(3+i)&0x80))
                    break;
            }
            if(_arr.size()!=(xxx.size()+3))
                break;
            temp.append(QString("wiRDSECTION"));
            bool dev = false;
            if(xxx.size()==5)
            {
                if(xxx.at(4)&0x80)
                    dev = true;
            }
            if(dev)
            {
                if(xxx.at(4)&0x40)
                    temp.append(" (prot)");
                else
                    temp.append(" (dev)");
                temp.append(QString(", nr: ")+QString::number(xxx.at(4)&0x3F));
            }
            else
            {
                temp.append(", nr: ");
                for(auto a: xxx)
                    temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
            }
            done = true;
        }
        }
        break;
    }
    case 0b10:
        break;
    case 0b11:
        break;
    default:
        break;
    }
    if(!done)
    {
        temp.append("Data: ");
        for(auto a:_arr)
            temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
    }

    temp.append(" ]");
    return temp;
}

QByteArray PureMessage::wiRDCONST(uint offset)
{
    QByteArray temp;
    temp.append((offset>>12)&0xF0);
    temp.append((offset>>0)&0xFF);
    temp.append((offset>>8)&0xFF);
    return temp;
}

QByteArray PureMessage::wiRDSECTION_dev(uint nr, bool prot)
{
    QByteArray temp;
    temp.append(wiRDSECTION_c);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80 | ((uint(prot)<<6)&0x40) | (nr&0x3F));
    return temp;
}
