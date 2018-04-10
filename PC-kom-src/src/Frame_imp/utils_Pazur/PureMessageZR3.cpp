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
        }
        break;
    }
    default:
        break;
    }

    return temp;
}

//QString PureMessage::desc()
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
