#include "FrameStawrov.hpp"
#include <QDebug>
#include <QApplication>

FrameStawrov::FrameStawrov(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameStawrov";
    dbg = QApplication::arguments().contains("-dbg");
}

bool FrameStawrov::isValid()
{
    if(!(pck.at(0)-0xFF))
    {
        errorString = "Invalid start byte";
        return false;
    }
    if(pck.size()-5!=pck.at(3))
    {
        errorString = "Invalid data length";
        return false;
    }
    if(pck.at(3)>27)
    {
        errorString = "Exceeded data length";
        return false;
    }
    if(pck.at(3)==0)
    {
        errorString = "Null data length";
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
    if(dbg)
    {
        QString pure = "PURE DATA: ";
        for(auto s: pck)
            pure.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
        pure.remove(pure.size()-1, 1);
        pure = pure.toUpper();
        pure = pure.replace("X", "x");
        return pure;
    }

    if(!isValid())
        return InvalidString();

    if(pck.at(3)!=0)
    {
        QByteArray cargo = pck.mid(4);
        cargo.remove(cargo.size()-1, 1);
        if(cargo.isEmpty())
            return "To nie powinno się zdarzyć.";

        QString tempR;
        if((cargo.at(0)-0x31)==0)
        {
            if((cargo.length()<6)||(((cargo.length()+1)%2)))
            {
                tempR = "Błędny format kanałów: ";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            tempR = QString("Kanały [S 0x%1, E 0x%2]: ").arg(cargo.at(1), 2, 16, QChar('0')).arg(cargo.at(2), 2, 16, QChar('0'));
            for(int i=3; i<cargo.length()-1; i+=2)
            {
                int tval = 0;
                tval |= (cargo.at(i+1)<<8)&0xFF00;
                tval |= (cargo.at(i)<<0)&0x00FF;
                tempR.append(QString("[ %1 ] ").arg(tval));
            }

            return tempR;
        }
        else if((cargo.at(0)-0x01)==0)
        {
            if(cargo.length()<3)
            {
                tempR = "Błędny format ustawień kanałów: ";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            if(cargo.length()!=(3+2*cargo.at(2)))
            {
                tempR = "Błędny rozmiar danych ustawień kanałów: ";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            tempR = QString("SET_CHANNELS [ADR 0x%1, CHS 0x%2]: ").arg(cargo.at(1)&0xff, 2, 16, QChar('0'))
                    .arg((cargo.at(2))&0xff, 2, 16, QChar('0'));
            for(int i=3; i<cargo.length(); i+=2)
            {
                int tval = 0;
                tval |= (cargo.at(i+1)<<8)&0xFF00;
                tval |= (cargo.at(i)<<0)&0x00FF;
                tempR.append(QString("[ 0x%1 ] ").arg(tval, 4, 16, QChar('0')));
            }
            return tempR;
        }
        else if((cargo.at(0)-0x02)==0)
        {
            tempR = "SYNCH_AND_START";
            return tempR;
        }
        else if((cargo.at(0)-0x03)==0)
        {
            if(cargo.length()<2)
            {
                tempR = "Błędny format RESET_SLAVE";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            tempR = QString("RESET_SLAVE [ADR: 0x%1]").arg(cargo.at(1)&0xff, 2, 16, QChar('0'));
            return tempR;
        }
        else if((cargo.at(0)-0x04)==0)
        {
            tempR = "RESET_MASTER";
            return tempR;
        }
        else if((cargo.at(0)-0x05)==0)
        {
            if(cargo.length()<4)
            {
                tempR = "Błędny format SET_HIGH_VOLTAGE: ";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            int tval = 0;
            tval |= (cargo.at(3)<<8)&0xFF00;
            tval |= (cargo.at(2)<<0)&0x00FF;
            tempR = QString("SET_HIGH_VOLTAGE [ADR: 0x%1, VOL: 0x%2]").arg(cargo.at(1)&0xff, 2, 16, QChar('0'))
                    .arg(tval, 4, 16, QChar('0'));
            return tempR;
        }
        else if((cargo.at(0)-0x06)==0)
        {
            if(cargo.length()<7)
            {
                tempR = "Błędny format SET_GAIN_OFFSET_AND_TRIGGER: ";
                for(auto s: cargo)
                    tempR.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
                return tempR;
            }
            int toff = 0, ttrig = 0;
            toff |= (cargo.at(4)<<8)&0xFF00;
            toff |= (cargo.at(3)<<0)&0x00FF;
            ttrig |= (cargo.at(6)<<8)&0xFF00;
            ttrig |= (cargo.at(5)<<0)&0x00FF;
            tempR = QString("SET_GAIN_OFFSET_AND_TRIGGER [ADR: 0x%1, GAIN: 0x%2, OFFSET: 0x%3, TRIGGER: 0x%4]")
                    .arg(cargo.at(1)&0xff, 2, 16, QChar('0'))
                    .arg(cargo.at(2)&0xff, 2, 16, QChar('0'))
                    .arg(toff, 4, 16, QChar('0'))
                    .arg(ttrig, 4, 16, QChar('0'));
            return tempR;
        }
    }

    QString temp = "Unknown header: ";
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

/**
 * Tak naprawdę to nie jest CRC16 tylko 1-bajtowy XOR.
 */
QByteArray FrameStawrov::AddCRC16(QByteArray data)
{
    char temp = 0x00;
    for(int i=1;i<data.length();++i)
        temp ^= data.at(i);
    data.append(temp);
    return data;
}

/**
 * Tak naprawdę to nie jest CRC16 tylko 1-bajtowy XOR.
 */
bool FrameStawrov::CheckCRC16(Frame* fr)
{
    char temp = 0x00;
    for(int i=1;i<fr->pureData().length()-1;++i)
        temp ^= fr->pureData().at(i);
    if(fr->pureData().at(fr->pureData().size()-1)!=temp)
        return false;
    return true;
}
