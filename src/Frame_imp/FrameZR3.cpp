#include "FrameZR3.hpp"

FrameZR3::FrameZR3(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameZR3";
}

bool FrameZR3::isValid()
{
    if(pck.at(0)!=(char)(0xFF))
    {
        invalidDesc = "invalid start";
        return false;
    }

    if(pck.at(4)!=pck.length()-6)
    {
        invalidDesc = "invalid length";
        return false;
    }

    if(!CheckLRC(pck))
    {
        invalidDesc = "invalid LRC";
        return false;
    }

    char val = pck.at(1)&0x1f;
    if((pck.at(1)&0x40)==0)
    {
        if((val==protSET_NEXT_ADR)||(val==protSET_ADR))
        {
            if(pck.at(4)!=(char)(0x01))
            {
                invalidDesc = "invalid data package on prot level";
                return false;
            }
        }
    }

    return true;
}

QString FrameZR3::toQString()
{
    if(!isValid())
        return invalidDesc;

    QString tstring;
    tstring.append(DirectString());
    tstring.append(ProtString());

    char val = pck.at(1)&0x1f;
    if((pck.at(1)&0x40)==0)
    {
        if(val==protDATA)
            tstring.append(AplString());
    }

    return tstring;
}

QString FrameZR3::toShortQString()
{
    return "XXX";
}

QByteArray FrameZR3::magicNumbers()
{
    return "XXX";
}

QString FrameZR3::DirectString()
{
    QString temp = "( ";
    temp.append(QString("0x%1 -> 0x%2 ").arg(((int)(pck.at(3)))&0xFF, 2, 16, QChar('0')).arg(((int)(pck.at(2)))&0xFF, 2, 16, QChar('0')));
    if(pck.at(1)&0x80)
        temp.append("[T] ");
    temp.append(") ");
    temp = temp.toUpper();
    temp = temp.replace("X", "x");
    return temp;
}

QString FrameZR3::ProtString()
{
    QString temp = "... ( ";

    char val = pck.at(1)&0x1f;

    if(pck.at(1)&0x40)
    {
        temp.append("protERROR: ");
        temp.append(protErrorNumbers.value(val, "Nieznany błąd"));
    }
    else
    {
        switch(val)
        {
        case protHOLLOW:
            temp.append("protHOLLOW ");
            break;
        case protHELLO:
            temp.append("protHELLO ");
            break;
        case protSET_ADR:
            temp.append(QString("protSET_ADR: 0x%1 ").arg(((int)(pck.at(5)))&0xFF, 2, 16, QChar('0')));
            break;
        case protSET_NEXT_ADR:
            temp.append(QString("protSET_NEXT_ADR: 0x%1 ").arg(((int)(pck.at(5)))&0xFF, 2, 16, QChar('0')));
            break;
        case protDATA:
            temp.append("protDATA ");
            break;
        default:
            temp.append(QString(" niznana komenda 0x%1 ").arg(((int)(val))&0xFF, 2, 16, QChar('0')));
        }
    }

    temp.append(") ");
    return temp;
}

QString FrameZR3::AplString()
{
    QString temp = "... ( ";

    QByteArray ba = pck.mid(5);
    ba.remove(ba.length()-1, 1);

    for(char ch:ba)
        temp.append(QString("0x%1 ").arg(((int)(ch))&0xFF, 2, 16, QChar('0')));

    temp.append(")");
    return temp;
}

char FrameZR3::CalcLRC(QByteArray ba)
{
    char LRC = 0x00;
    for(char ch:ba)
        LRC += ch;
    LRC ^= 0xFF;
    LRC += 0x01;
    return LRC;
}

void FrameZR3::AppendLRC(QByteArray &ba)
{
    ba.append(FrameZR3::CalcLRC(ba.mid(1)));
}

/**
 * true - ok, false - błędna LRC.
 */
bool FrameZR3::CheckLRC(QByteArray &ba)
{
    if(ba.at(ba.length()-1) == CalcLRC(ba.mid(1, ba.length()-2)))
        return true;
    return false;
}
