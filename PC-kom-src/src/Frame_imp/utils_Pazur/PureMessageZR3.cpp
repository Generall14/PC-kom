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
        }
        break;
    }
    default:
        break;
    }

    return temp;
}

//QString PureMessage::desc() const
//{
//    QString temp = " [";
//
//    bool done = false;

//    switch(inf)
//    {
//        //=====================================================================================================================
//    case 0b00:
//    {
//        uchar code00 = _arr.at(2)&0x1F;
//        switch(code00)
//        {
//        case wkpSTORE_c:
//        {
//            if(3!=_arr.size())
//                break;
//            temp.append(QString("wkpSTORE"));
//            done = true;
//            break;
//        }
//        case wkpCONNECT_c:
//        {
//            if(3!=_arr.size())
//                break;
//            temp.append(QString("wkpCONNECT"));
//            done = true;
//            break;
//        }
//        case wkpCONNECTo_c:
//        {
//            if(4!=_arr.size())
//                break;
//            temp.append(QString("wkpCONNECTo, nastepnik: 0x%1").arg(_arr.at(3)&0x3F, 2, 16, QChar('0')));
//            done = true;
//            break;
//        }
//        case wkpBUILD_c:
//        {
//            if(3!=_arr.size())
//                break;
//            temp.append(QString("wkpBUILD"));
//            done = true;
//            break;
//        }
//        case wkpBUILDo_c:
//        {
//            if(3!=_arr.size())
//                break;
//            temp.append(QString("wkpBUILDo"));
//            done = true;
//            break;
//        }
//        case wkpRESET_c:
//        {
//            if(3!=_arr.size())
//                break;
//            temp.append(QString("wkpRESET"));
//            done = true;
//            break;
//        }
//        }
//        break;
//    }
//        //=====================================================================================================================
//    case 0b01:
//    {
//        uchar code01 = _arr.at(2)&0x0F;
//        switch (code01)
//        {
//        case wiRDCONST_c:
//        {
//            if(_arr.size()!=5)
//                break;
//            uint off = 0;
//            off |= _arr.at(3)&0xFF;
//            off |= (_arr.at(4)<<8)&0xFF00;
//            off |= (_arr.at(2)<<12)&0xF0000;
//            temp.append(QString("wiRDCONST, offset: 0x%1").arg(off, 5, 16, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiRDCONSTo_c:
//        {
//            if(_arr.size()<5)
//                break;
//            uint off = 0;
//            off |= _arr.at(3)&0xFF;
//            off |= (_arr.at(4)<<8)&0xFF00;
//            off |= (_arr.at(2)<<12)&0xF0000;
//            temp.append(QString("wiRDCONSTo, offset: 0x%1, data:").arg(off, 5, 16, QChar('0')));
//            for(int i=5;i<_arr.size();++i)
//                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiRDSECTION_c:
//        {
//            if(_arr.size()<4)
//                break;
//            QByteArray xxx;
//            for(int i=0;i<5;++i)
//            {
//                if(3+i>=_arr.size())
//                    break;
//                xxx.append(_arr.at(3+i));
//                if(!(_arr.at(3+i)&0x80))
//                    break;
//            }
//            if(_arr.size()!=(xxx.size()+3))
//                break;
//            temp.append(QString("wiRDSECTION"));
//            bool dev = false;
//            if(xxx.size()==5)
//            {
//                if(xxx.at(4)&0x80)
//                    dev = true;
//            }
//            if(dev)
//            {
//                if(xxx.at(4)&0x40)
//                    temp.append(" (prot)");
//                else
//                    temp.append(" (dev)");
//                temp.append(QString(", nr: ")+QString::number(xxx.at(4)&0x3F));
//            }
//            else
//            {
//                temp.append(", nr: ");
//                for(auto a: xxx)
//                    temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//            }
//            done = true;
//            break;
//        }
//        case wiRDSECTIONo_c:
//        {
//            if(_arr.size()<4)
//                break;
//            QByteArray xxx;
//            for(int i=0;i<5;++i)
//            {
//                if(3+i>=_arr.size())
//                    break;
//                xxx.append(_arr.at(3+i));
//                if(!(_arr.at(3+i)&0x80))
//                    break;
//            }
//            temp.append(QString("wiRDSECTIONo"));
//            bool fatal = false;
//            if(_arr.at(2)&0x10)
//                fatal = true;
//            bool dev = false;
//            if(xxx.size()==5)
//            {
//                if(xxx.at(4)&0x80)
//                    dev = true;
//            }
//            if(dev)
//            {
//                if(xxx.at(4)&0x40)
//                    temp.append(" (prot)");
//                else
//                    temp.append(" (dev)");
//                temp.append(QString(", nr: ")+QString::number(xxx.at(4)&0x3F));
//            }
//            else
//            {
//                temp.append(", nr: ");
//                for(auto a: xxx)
//                    temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//            }
//            if(!fatal)
//            {
//                temp.append(", data: ");
//                for(int i=xxx.size()+3;i<_arr.size();++i)
//                    temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
//            }
//            else
//                temp.append(", nie rozpoznano sekcji");
//            done = true;
//            break;
//        }
//        case wiWRSECTION_c:
//        {
//            if(_arr.size()<6)
//                break;
//            QByteArray xxx;
//            for(int i=0;i<5;++i)
//            {
//                if(5+i>=_arr.size())
//                    break;
//                xxx.append(_arr.at(5+i));
//                if(!(_arr.at(5+i)&0x80))
//                    break;
//            }
//            temp.append(QString("wiWRSECTION"));
//            bool dev = false;
//            if(xxx.size()==5)
//            {
//                if(xxx.at(4)&0x80)
//                    dev = true;
//            }
//            if(dev)
//            {
//                if(xxx.at(4)&0x40)
//                    temp.append(" (prot)");
//                else
//                    temp.append(" (dev)");
//                temp.append(QString(", nr: ")+QString::number(xxx.at(4)&0x3F));
//            }
//            else
//            {
//                temp.append(", nr: ");
//                for(auto a: xxx)
//                    temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//            }
//            temp.append(QString(", magic: 0x%1%2, data: ").arg((uint)_arr.at(4)&0xFF, 2, 16, QChar('0'))
//                        .arg((uint)_arr.at(3)&0xFF, 2, 16, QChar('0')));
//            for(int i=xxx.size()+5;i<_arr.size();++i)
//                temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiWARN_c:
//        {
//            if(_arr.size()<4)
//                break;
//            temp.append("wiWARN, flags: ");
//            for(int i=3;i<_arr.size();++i)
//                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiFAULT_c:
//        {
//            if(_arr.size()<4)
//                break;
//            temp.append("wiFAULT, flags: ");
//            for(int i=3;i<_arr.size();++i)
//                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiSERVICE_c:
//        {
//            if(_arr.size()<4)
//                break;
//            temp.append("wiSERVICE, flags: ");
//            for(int i=3;i<_arr.size();++i)
//                temp.append(QString("0b%1-%2").arg((uint)(_arr.at(i)>>4)&0x0F, 4, 2, QChar('0')).arg((uint)_arr.at(i)&0x0F, 4, 2, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiGFDA_c:
//        {
//            if(_arr.size()<4)
//                break;
//            QByteArray xxx;
//            for(int i=0;i<5;++i)
//            {
//                if(3+i>=_arr.size())
//                    break;
//                xxx.append(_arr.at(3+i));
//                if(!(_arr.at(3+i)&0x80))
//                    break;
//            }
//            temp.append(QString("wiGFDA"));
//            if(_arr.at(2)&0x40)
//                temp.append(", UTKAK, code: ");
//            else
//                temp.append(", UTKK, code:");
//            for(auto a: xxx)
//                temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//            done = true;
//            break;
//        }
//        case wiGFDAo_c:
//        {
//            if(_arr.size()<4)
//                break;
//            QByteArray xxx;
//            for(int i=0;i<5;++i)
//            {
//                if(3+i>=_arr.size())
//                    break;
//                xxx.append(_arr.at(3+i));
//                if(!(_arr.at(3+i)&0x80))
//                    break;
//            }
//            temp.append(QString("wiGFDAo"));
//            if(_arr.at(2)&0x40)
//                temp.append(", UTKAK, code: ");
//            else
//                temp.append(", UTKK, code: ");
//            for(auto a: xxx)
//                temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//            if(_arr.at(2)&0x80)
//                temp.append(", nie rozpoznano sekcji");
//            else
//            {
//                temp.append(", data: ");
//                for(int i=xxx.size()+3;i<_arr.size();++i)
//                    temp.append(QString("0x%1 ").arg((uint)_arr.at(i)&0xFF, 2, 16, QChar('0')));
//            }
//            done = true;
//            break;
//        }
//        }
//        break;
//    }
//        //=====================================================================================================================
//    case 0b10:
//        //=====================================================================================================================
//    case 0b11:
//        break;
//        //=====================================================================================================================
//    default:
//        break;
//    }
//    if(!done)
//    {
//        temp.append("Data: ");
//        for(auto a:_arr)
//            temp.append(QString("0x%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
//    }

//    temp.append(" ]");
//    return temp;
//}

//QByteArray PureMessage::wiRDCONST(uint offset)
//{
//    QByteArray temp;
//    temp.append((offset>>12)&0xF0);
//    temp.append((offset>>0)&0xFF);
//    temp.append((offset>>8)&0xFF);
//    return temp;
//}

//QByteArray PureMessage::wiRDSECTION_dev(uint nr, bool prot)
//{
//    QByteArray temp;
//    temp.append(wiRDSECTION_c);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80 | ((uint(prot)<<6)&0x40) | (nr&0x3F));
//    return temp;
//}

//QByteArray PureMessage::wiRDSECTION_long(QByteArray nr)
//{
//    QByteArray temp;
//    temp.append(wiRDSECTION_c);
//    for(int i=0;i<5;++i)
//    {
//        if(i>=nr.size())
//            break;
//        temp.append(nr.at(i));
//        if(!(nr.at(i)&0x80))
//            break;
//    }
//    return temp;
//}

//QByteArray PureMessage::wiWRSECTION_dev(uint nr, bool prot, uint16_t magic, QByteArray data)
//{
//    QByteArray temp;
//    temp.append(wiWRSECTION_c);
//    temp.append(magic&0xFF);
//    temp.append((magic>>8)&0xFF);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80);
//    temp.append(0x80 | ((uint(prot)<<6)&0x40) | (nr&0x3F));
//    temp.append(data);
//    return temp;
//}

//QByteArray PureMessage::wiWRSECTION_long(QByteArray nr, uint16_t magic, QByteArray data)
//{
//    QByteArray temp;
//    temp.append(wiWRSECTION_c);
//    temp.append(magic&0xFF);
//    temp.append((magic>>8)&0xFF);
//    for(int i=0;i<5;++i)
//    {
//        if(i>=nr.size())
//            break;
//        temp.append(nr.at(i));
//        if(!(nr.at(i)&0x80))
//            break;
//    }
//    temp.append(data);
//    return temp;
//}

//QByteArray PureMessage::wiGFDA(bool utkak, QByteArray nr)
//{
//    QByteArray temp;
//    temp.append(wiGFDA_c);
//    int end = 5;
//    if(utkak)
//    {
//        end = 3;
//        temp[0] = temp[0]|0x40;
//    }
//    for(int i=0;i<end;++i)
//    {
//        if(i>=nr.size())
//            break;
//        temp.append(nr.at(i));
//        if(!(nr.at(i)&0x80))
//            break;
//    }
//    return temp;
//}

//QByteArray PureMessage::wkpSTORE()
//{
//    QByteArray temp;
//    temp.append(wkpSTORE_c);
//    return temp;
//}

//QByteArray PureMessage::wkpCONNECT()
//{
//    QByteArray temp;
//    temp.append(wkpCONNECT_c);
//    return temp;
//}

//QByteArray PureMessage::wkpCONNECTo(QByteArray next)
//{
//    if(next.isEmpty())
//        return QByteArray();
//    QByteArray temp;
//    temp.append(wkpCONNECTo_c);
//    temp.append(next.at(0));
//    return temp;
//}

//QByteArray PureMessage::wkpBUILD()
//{
//    QByteArray temp;
//    temp.append(wkpBUILD_c);
//    return temp;
//}

//QByteArray PureMessage::wkpBUILDo()
//{
//    QByteArray temp;
//    temp.append(wkpBUILDo_c);
//    return temp;
//}

//QByteArray PureMessage::wkpRESET()
//{
//    QByteArray temp;
//    temp.append(wkpRESET_c);
//    return temp;
//}

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