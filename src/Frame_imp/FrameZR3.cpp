#include "FrameZR3.hpp"
#include <QDebug>

FrameZR3::FrameZR3(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameZR3";

    if(pck.size()<2)
        return;
    if(pck.at(0)==(char)(0xFD))
        pck.insert(0, (char)(0xFF));
}

bool FrameZR3::isValid()
{
    if(pck.at(0)!=(char)(0xFF))
    {
        invalidDesc = "invalid start";
        return false;
    }

    if(pck.at(1)!=(char)(0xFD))
    {
        invalidDesc = "invalid start";
        return false;
    }

    if(pck.at(2)&0x40)
    {
        if((pck.at(2)&0x3F)!=pck.length()-7)
        {
            invalidDesc = "invalid length";
            return false;
        }
    }

    if(!CheckLRC(pck))
    {
        invalidDesc = "invalid CRC_CCITT";
        return false;
    }

//    char val = pck.at(1)&0x1f;
//    if((pck.at(1)&0x40)==0)
//    {
//        if((val==protSET_NEXT_ADR)||(val==protSET_ADR))
//        {
//            if(pck.at(4)!=(char)(0x01))
//            {
//                invalidDesc = "invalid data package on prot level";
//                return false;
//            }
//        }
//    }

    return true;
}

QString FrameZR3::toQString()
{
    if(!isValid())
        return invalidDesc;

    QString tstring;
    tstring.append(DirectString());
    tstring.append(ProtString());

    if(magicNumbers().at(0)&0x40)
        tstring.append(AplString());

    return tstring;
}

QString FrameZR3::toShortQString()
{
    return "XXX";
}

QByteArray FrameZR3::magicNumbers()
{
    QByteArray temp;
    if(isValid())
    {
        if(pck.at(2)&0x40)
            temp.append(pck.at(2)&0xC0);
        else
            temp.append(pck.at(2)&0xBF);
    }
    return temp;
}

QByteArray FrameZR3::aplData()
{
    QByteArray temp;
    if(isValid())
    {
        if(pck.at(2)&0x40)
        {
            temp.append(pck.mid(5, pck.at(2)&0x3F));
        }
    }
    return temp;
}

QByteArray FrameZR3::srcAdr()
{
    QByteArray temp;
    if(isValid())
        temp.append(pck.at(4));
    return temp;
}

QByteArray FrameZR3::dstAdr()
{
    QByteArray temp;
    if(isValid())
        temp.append(pck.at(3));
    return temp;
}

QString FrameZR3::DirectString()
{
    QString temp = "( ";
    temp.append(QString("0x%1 -> 0x%2 ").arg(srcAdr().at(0)&0xFF, 2, 16, QChar('0')).arg(dstAdr().at(0)&0xFF, 2, 16, QChar('0')));
    if(magicNumbers().at(0)&0x80)
        temp.append("[T] ");
    temp.append(") ");
    temp = temp.toUpper();
    temp = temp.replace("X", "x");
    return temp;
}

QString FrameZR3::ProtString()
{
    QString temp = "... ( ";

    char val = magicNumbers().at(0);

    if(val&0x40)
    {
        temp.append("protDATA ");
    }
    else
    {
        val &= 0x3F;
        switch(val)
        {
        case protHOLLOW:
            temp.append("protHOLLOW ");
            break;
        case protHELLO:
            temp.append("protHELLO ");
            break;
        case protDEV_ID:
            temp.append("protDEV_ID , sNum=\"");
            if(pck.length()<11+7)
                break;
            temp.append(pck.mid(5, 10)+"\", protV="+QString::number(pck.at(15)));
            break;
        default:
            temp.append(QString(" niznana komenda 0x%1 ").arg(((int)(val))&0xFF, 2, 16, QChar('0')));
        }
    }


//    if(pck.at(1)&0x40)
//    {
//        temp.append("protERROR: ");
//        temp.append(protErrorNumbers.value(val, "Nieznany błąd"));
//    }
//    else
//    {
//        switch(val)
//        {
//        case protSET_ADR:
//            temp.append(QString("protSET_ADR: 0x%1 ").arg(((int)(pck.at(5)))&0xFF, 2, 16, QChar('0')));
//            break;
//        case protSET_NEXT_ADR:
//            temp.append(QString("protSET_NEXT_ADR: 0x%1 ").arg(((int)(pck.at(5)))&0xFF, 2, 16, QChar('0')));
//            break;
//        }
//    }

    temp.append(") ");
    return temp;
}

QString FrameZR3::AplString()
{
    QString temp = "... ( ";

    QByteArray ba = pck.mid(5);
    ba.remove(ba.length()-1, 1);

    uchar val = ba.at(0);
    QByteArray rest;
    uint16_t off = 0;
    uint8_t siz = 0;
//    switch(val)
//    {
//    case 0x0A:
//        off |= (ba.at(1)<<8)&0xFF00;
//        off |= (ba.at(2)<<0)&0x00FF;
//        siz = ba.at(3);
//        temp.append(QString("aplStringListDescriptor req offset=0x%1 size=0x%2").arg(((int)(off))&0xFFFF, 4, 16, QChar('0'))\
//                    .arg(((int)(siz))&0xFF, 2, 16, QChar('0')));
//        break;
//    case 0x8A:
//        temp.append("aplStringListDescriptor resp: ");
//        rest = ba.mid(1);
//        break;
//    case 0x01:
//        off |= (ba.at(1)<<8)&0xFF00;
//        off |= (ba.at(2)<<0)&0x00FF;
//        siz = ba.at(3);
//        temp.append(QString("aplDeviceDescriptor req offset=0x%1 size=0x%2").arg(((int)(off))&0xFFFF, 4, 16, QChar('0'))\
//                    .arg(((int)(siz))&0xFF, 2, 16, QChar('0')));
//        break;
//    case 0x81:
//        temp.append("aplDeviceDescriptor resp: ");
//        rest = ba.mid(1);
//        break;
//    case 0x09:
//        off |= (ba.at(1)<<8)&0xFF00;
//        off |= (ba.at(2)<<0)&0x00FF;
//        siz = ba.at(3);
//        temp.append(QString("aplMethodDescriptor req offset=0x%1 size=0x%2").arg(((int)(off))&0xFFFF, 4, 16, QChar('0'))\
//                    .arg(((int)(siz))&0xFF, 2, 16, QChar('0')));
//        break;
//    case 0x89:
//        temp.append("aplMethodDescriptor resp: ");
//        rest = ba.mid(1);
//        break;
//    default:
//        temp.append("??? ");
//        rest = ba;
//        break;
//    }

    for(char ch:rest)
        temp.append(QString("0x%1 ").arg(((int)(ch))&0xFF, 2, 16, QChar('0')));

    temp.append(")");
    return temp;
}

uint16_t FrameZR3::CalcLRC(QByteArray arr, uint16_t sum)
{
    const uint16_t pol = 0x1021;
    for(int i=0;i<arr.size()+2;++i)
    {
        uint8_t lval = 0x00;
        if(i<arr.size())
            lval = arr.at(i);
        for(int i=0;i<8;++i)
        {
            bool needxor = sum&0x8000;
            sum <<= 1;

            if(lval&0x80)
                sum |= 0x01;
            lval <<= 1;

            if(needxor)
                sum ^= pol;
        }
    }
    return sum;
}

void FrameZR3::AppendCRC(QByteArray &ba)
{
    int from = 2;
    if(ba.at(0)==(char)(0xFD))
        from = 1;
    uint16_t crc = CalcLRC(ba.mid(from));
    ba.append((crc>>8)&0xFF);
    ba.append(crc&0xFF);
}

/**
 * true - ok, false - błędna LRC.
 */
bool FrameZR3::CheckLRC(QByteArray &ba)
{
    int from = 2;
    if(ba.at(0)==(char)(0xFD))
        from = 1;
    if(CalcLRC(ba.mid(from)))
        return false;
    return true;
}
