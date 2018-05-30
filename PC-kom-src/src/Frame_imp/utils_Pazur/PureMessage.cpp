#include "PureMessage.hpp"
#include <cassert>
#include <QDebug>
#include "PureMessageZR3.hpp"

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

    switch(inf)
    {
        //=====================================================================================================================
    case 0b00:
    {
        uchar code00 = _arr.at(2)&0x1F;
        switch(code00)
        {
        case wkpSTORE_c:
        {
            if(3!=_arr.size())
                break;
            temp.append(QString("wkpSTORE"));
            done = true;
            break;
        }
        case wkpCONNECT_c:
        {
            if(3!=_arr.size())
                break;
            temp.append(QString("wkpCONNECT"));
            done = true;
            break;
        }
        case wkpCONNECTo_c:
        {
            if(4!=_arr.size())
                break;
            temp.append(QString("wkpCONNECTo, nastepnik: 0x%1").arg(_arr.at(3)&0x3F, 2, 16, QChar('0')));
            done = true;
            break;
        }
        case wkpBUILD_c:
        {
            if(3!=_arr.size())
                break;
            temp.append(QString("wkpBUILD"));
            done = true;
            break;
        }
        case wkpBUILDo_c:
        {
            if(3!=_arr.size())
                break;
            temp.append(QString("wkpBUILDo"));
            done = true;
            break;
        }
        case wkpRESET_c:
        {
            if(3!=_arr.size())
                break;
            temp.append(QString("wkpRESET"));
            done = true;
            break;
        }
        }
        break;
    }
        //=====================================================================================================================
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
            temp.append(QString("wiRDSECTION, nr: "));
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            break;
        }
        case wiRDSECTIONo_c:
        {
            if(_arr.size()<4)
                break;
            temp.append(QString("wiRDSECTIONo"));
            bool fatal = false;
            if(_arr.at(2)&0x10)
                fatal = true;
            if(fatal)
                temp.append(", nie rozpoznano sekcji, ");
            temp.append(", all:");
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            break;
        }
        case wiWRSECTION_c:
        {
            if(_arr.size()<6)
                break;
            temp.append(QString("wiWRSECTION, all: "));
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            break;
        }
        case wiWARN_c:
        {
            if(_arr.size()<4)
                break;
            temp.append("wiWARN, flags: ");
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
            done = true;
            break;
        }
        case wiFAULT_c:
        {
            if(_arr.size()<4)
                break;
            temp.append("wiFAULT, flags: ");
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
            done = true;
            break;
        }
        case wiSERVICE_c:
        {
            if(_arr.size()<4)
                break;
            temp.append("wiSERVICE, flags: ");
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
            done = true;
            break;
        }
        case wiGFDA_c:
        {
            if(_arr.size()<4)
                break;
            temp.append(QString("wiGFDA, all: "));
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            done = true;
            break;
        }
        case wiGFDAo_c:
        {
            if(_arr.size()<4)
                break;
            temp.append(QString("wiGFDAo"));
            bool fatal = false;
            if(_arr.at(2)&0x80)
                fatal = true;
            if(fatal)
                temp.append(", nie rozpoznano sekcji, ");
            temp.append(", all:");
            for(int i=3;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            done = true;
            break;
        }
        }
        break;
    }
        //=====================================================================================================================
    default:
        temp.append(PureMessageZR3::desc(_arr, &done));
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

QByteArray PureMessage::wiRDSECTION_long(QByteArray nr)
{
    QByteArray temp;
    temp.append(wiRDSECTION_c);
    for(int i=0;i<8;++i)
    {
        if(i>=nr.size())
            break;
        temp.append(nr.at(i));
    }
    return temp;
}

QByteArray PureMessage::wiWRSECTION_dev(uint nr, bool prot, uint16_t magic, QByteArray data)
{
    QByteArray temp;
    temp.append(wiWRSECTION_c);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80 | ((uint(prot)<<6)&0x40) | (nr&0x3F));
    temp.append(data);
    return temp;
}

QByteArray PureMessage::wiWRSECTION_long(QByteArray nr, uint16_t magic, QByteArray data)
{
    QByteArray temp;
    temp.append(wiWRSECTION_c);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);
    for(int i=0;i<8;++i)
    {
        if(i>=nr.size())
            break;
        temp.append(nr.at(i));
    }
    temp.append(data);
    return temp;
}

QByteArray PureMessage::wiGFDA(bool utkak, QByteArray nr)
{
    QByteArray temp;
    temp.append(wiGFDA_c);
    int end = 8;
    if(utkak)
    {
        end = 3;
        temp[0] = temp[0]|0x40;
    }
    for(int i=0;i<end;++i)
    {
        if(i>=nr.size())
            break;
        temp.append(nr.at(i));
    }
    return temp;
}

QByteArray PureMessage::wkpSTORE()
{
    QByteArray temp;
    temp.append(wkpSTORE_c);
    return temp;
}

QByteArray PureMessage::wkpCONNECT()
{
    QByteArray temp;
    temp.append(wkpCONNECT_c);
    return temp;
}

QByteArray PureMessage::wkpCONNECTo(QByteArray next)
{
    if(next.isEmpty())
        return QByteArray();
    QByteArray temp;
    temp.append(wkpCONNECTo_c);
    temp.append(next.at(0));
    return temp;
}

QByteArray PureMessage::wkpBUILD()
{
    QByteArray temp;
    temp.append(wkpBUILD_c);
    return temp;
}

QByteArray PureMessage::wkpBUILDo()
{
    QByteArray temp;
    temp.append(wkpBUILDo_c);
    return temp;
}

QByteArray PureMessage::wkpRESET()
{
    QByteArray temp;
    temp.append(wkpRESET_c);
    return temp;
}

/**
 * Oblicza magiczny numer potrzebny do zapisywania danych na podstawie odczytanego wID_IDX.
 * @param wID_IDX - dane wID_IDX (od początku, co najmniej xxx bajtów)
 */
uint PureMessage::calcMagicNumber(QByteArray wID_IDX)
{
    uint temp = 0x0000;
    if(wID_IDX.size()<11)
        return temp;
    temp += wID_IDX.at(5);
    temp += wID_IDX.at(6);
    temp += wID_IDX.at(8);
    temp += wID_IDX.at(9);
    temp += wID_IDX.at(10);
    return temp;
}
