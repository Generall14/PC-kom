#include "sg1frame.h"

SG1Frame::SG1Frame(QByteArray ba)
{
    this->FromQByteArray(ba);
}

void SG1Frame::FromQByteArray(QByteArray ba)
{
    pck = ba;
}

bool SG1Frame::isValid()
{
    if(pck.size()!=5)
        return false;
    if((pck.at(0)^pck.at(4))!=char(0xFF))
        return false;
    return true;
}

QString SG1Frame::toQString()
{
    float timeres = 0.5;
    float voltage, k = 3.3*(560.0+6200.0)/(560.0)/256;
    int result;
    int mlv=0, llv=0;

    if(this->isValid())
    {
        result = 0;
        result |= (pck[1]<<16)&0xFF0000;
        result |= (pck[2]<<8)&0xFF00;
        result |= pck[3]&0xFF;

        switch (pck.at(0))
        {
        case 'C':                           //Pomiar
            result /= timeres;
            return QString("Raport: pomiar: %1 imp/s").arg(result, 8, 10);
            break;
        case 'A':                           //Licznik kalibracji
            return QString("Raport: pomiar autokalibracji: %1 imp").arg(result, 8, 10);
            break;
        case 't':                           //Temperatura
            return QString("Raport: temperatura: %1 ADC").arg(result, 8, 10);
            break;
        case 'Z':                           //Zatkanie
            return QString("Raport: pomiar zatkania: %1 ADC").arg(result, 8, 10);
            break;
        case 'L':                           //Poziomy
            mlv=0;
            llv=0;
            mlv |= pck[2]&0xFF;
            llv |= pck[3]&0xFF;
            llv = 8-llv;
            return QString("Raport: poziomy progów: %1/%2").arg(mlv, 0, 10).arg(llv, 0, 10);
            break;
        case 'D':                           //Zmiana napięcie
            voltage = (float)result*k;
            return QString("Raport: napięcie SiPM: %1 DAC, ").arg(result, 0, 10) +QString::number(voltage)+" V";
            break;
        default:
            return QString("Kij wie co");
        }

    }
    else
    {
        return "Invalid frame.";
    }
}
