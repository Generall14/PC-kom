#include "FrameStawrov.hpp"

FrameStawrov::FrameStawrov(QByteArray ba)
    :Frame(ba)
{}

bool FrameStawrov::isValid()
{
    if(!(pck.at(0)-0xFF))
    {
        errorString = "Invalid start byte";
        return false;
    }
    if(pck.size()-6!=pck.at(3))
    {
        errorString = "Invalid data length";
        return false;
    }
    if(!CheckCRC16(this))
    {
        errorString = "Invalid CRC";
        return false;
    }
    return true;
}

QString FrameStawrov::toQString()
{
    if(!isValid())
        return InvalidString();

    if((pck.at(3)-0x08)==0)
    {
        QString tempR = "Kanały: ";
        QByteArray cutArray = pck.mid(4);
        int tval;
        for(int i=0;i<4;i++)
        {
            tval = 0;
            tval |= (cutArray.at(0)<<8)&0xFF00;
            tval |= (cutArray.at(1)<<0)&0x00FF;
            tempR.append(QString("[ %1 ] ").arg(tval));
            cutArray = cutArray.mid(2);
        }
        return tempR;
    }

    QString temp = "Kij wie co: ";
    for(auto s: pck)
        temp.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
    temp.remove(temp.size()-1, 1);
    temp = temp.toUpper();
    temp = temp.replace("X", "x");
    return temp;
}

QString FrameStawrov::toShortQString()
{
    return "XXX";
}

QByteArray FrameStawrov::magicNumbers()
{
    return "XXX";
}

QString FrameStawrov::InvalidString()
{
    QString temp = errorString + ": ";
    for(auto s: pck)
        temp.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
    temp.remove(temp.size()-1, 1);
    temp = temp.toUpper();
    temp = temp.replace("X", "x");
    return temp;
}

QByteArray FrameStawrov::AddCRC16(QByteArray data)
{
    data.append(0x66);
    data.append(0x77);
    return data;
}

bool FrameStawrov::CheckCRC16(Frame* fr)
{
//    if(fr->pureData().at(fr->pureData().size()-1)!=0x77)
//        return false;
//    if(fr->pureData().at(fr->pureData().size()-2)!=0x66)
//        return false;
    return true;
}
