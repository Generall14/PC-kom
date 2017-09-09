#include "FrameSG1.hpp"

FrameSG1::FrameSG1(QByteArray ba)
    :Frame(ba)
{}

bool FrameSG1::isValid()
{
    if(pck.length()!=5)
        return false;
    int temp = pck.at(4);
    temp ^= 0xFF;
    if(temp!=(int)pck.at(0))
        return false;
    return true;
}

QString FrameSG1::toQString()
{
    if(!isValid())
        return InvalidString();

    int result;

    result = 0;
    result |= (pck[1]<<16)&0xFF0000;
    result |= (pck[2]<<8)&0xFF00;
    result |= pck[3]&0xFF;

    if((pck[0]&0xF0)==0x10)
    {
        int calNr = pck[0]&0x0F;
        return QString("Odczyt zmiennej kalibracjyjnej nr. %1: %2").arg(calNr, 2, 10).arg(result, 8, 10);
    }

    QString temp;
    for(auto s: pck)
        temp.append(QString("0x%1 ").arg((int)(s), 2, 16, QChar('0')));
    return QString("Kij wie co: "+temp);
}

QString FrameSG1::InvalidString()
{
    QString temohex;
    for(auto s: pck)
        temohex.append(QString("0x%1 ").arg((int)(s), 2, 16, QChar('0')));
    temohex = temohex.toUpper();
    temohex = temohex.replace("x", "X");

    if(pck.length()!=5)
        return "Nieprawidłowa długość ramki: " + temohex;

    if(pck.length()>=5)
    {
        int tempi = pck.at(4);
        tempi ^= 0xFF;
        if(tempi!=(int)pck.at(0))
            return "Niezgodność nagłówka i dopełnienia: " + temohex;
    }

    return "Nieznany nagłówek: " + temohex;
}
