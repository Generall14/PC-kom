#include "PureMessageZR3.hpp"
#include <cassert>
#include <QDebug>

QString PureMessageZR3::desc(QByteArray _arr, bool* found)
{
    QString temp;
    *found = false;

    uchar inf = (_arr.at(0)>>6)&0x03;
    switch(inf)
    {
        //=====================================================================================================================
    case 0b10:
    {
        break;
    }
        //=====================================================================================================================
    case 0b11:
    {
        uchar code11 = _arr.at(2)&0x3F;
        switch(code11)
        {
        case techREQ_c:
        {
            if(_arr.size()!=9)
                break;
            if((_arr.at(5)!=0x70)||(_arr.at(6)!=0x75)||(_arr.at(7)!=0x70)||(_arr.at(8)!=0x61))
                break;
            temp.append(QString("techREQ, magic: 0x%1%2").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techINV_c:
        {
            if(_arr.size()!=5)
                break;
            temp.append(QString("techINV, rnd: 0x%1%2").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techACC_c:
        {
            if(_arr.size()!=14)
                break;
            if((_arr.at(7)!=0x77)||(_arr.at(8)!=0x63)||(_arr.at(9)!=0x68)||(_arr.at(10)!=0x6F))
                break;
            if((_arr.at(11)!=0x64)||(_arr.at(12)!=0x7A)||(_arr.at(13)!=0x65))
                break;
            temp.append(QString("techACC, magic: 0x%1%2, rnd: 0x%3%4").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')).arg((uint)_arr.at(6)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(5)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techCONF_c:
        {
            if(_arr.size()!=5)
                break;
            temp.append(QString("techCONF, wersja programu: 0x%1%2").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techRDSECTION_c:
        {
            if(_arr.size()!=4)
                break;
            temp.append(QString("techRDSECTION, nr: 0x%1").arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techRDSECTIONo_c:
        {
            if(_arr.size()<4)
                break;
            temp.append(QString("techRDSECTIONo, nr: 0x%1").arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            if(_arr.at(2)&0x40)
                temp.append(", nie rozpoznano sekcji");
            else
                temp.append(", data: ");
                for(int i=4;i<_arr.size();++i)
                    temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        case techWRSECTION_c:
        {
            if(_arr.size()<6)
                break;
            temp.append(QString("techWRSECTION, nr: 0x%1").arg((uint)_arr.at(5)&0xFF, 2, 16, QChar('0')));
            temp.append(QString(", magic: 0x%1%2, data: ").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
            for(int i=6;i<_arr.size();++i)
                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
            *found = true;
            break;
        }
        }
        break;
    }
    default:
        break;
    }

    return temp;
}

QByteArray PureMessageZR3::techREQ(uint16_t magic)
{
    QByteArray temp;
    temp.append(techREQ_c);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);
    temp.append(0x70);
    temp.append(0x75);
    temp.append(0x70);
    temp.append(0x61);
    return temp;
}

QByteArray PureMessageZR3::techACC(uint16_t magic, uint16_t rnd)
{
    QByteArray temp;
    temp.append(techACC_c);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);
    temp.append(rnd&0xFF);
    temp.append((rnd>>8)&0xFF);
    temp.append(0x77);
    temp.append(0x63);
    temp.append(0x68);
    temp.append(0x6F);
    temp.append(0x64);
    temp.append(0x7A);
    temp.append(0x65);
    return temp;
}

QByteArray PureMessageZR3::techRDSECTION(uint nr)
{
    QByteArray temp;
    temp.append(techRDSECTION_c);
    temp.append(nr&0xFF);
    return temp;
}

QByteArray PureMessageZR3::techWRSECTION(uint nr, uint16_t magic, QByteArray data)
{
    QByteArray temp;
    temp.append(techWRSECTION_c);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);
    temp.append(nr&0xFF);
    temp.append(data);
    return temp;
}
