#include "FrameSG1.hpp"

float FrameSG1::timeres = 0.5;

FrameSG1::FrameSG1(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameSG1";

    errorNumbers.insert(0x3A, "ERROR_TEST");
    errorNumbers.insert(0x01, "UNIVERSAL_ERROR");
    errorNumbers.insert(0x02, "ACAL_UNEXPECTED_NOISE");
    errorNumbers.insert(0x03, "ACAL_OUT_OF_VOLTAGE");
    errorNumbers.insert(0x04, "NO_SIGNAL_ON_CDETECT");
    errorNumbers.insert(0x05, "LOST_SIPM_SIGNAL");
}

bool FrameSG1::isValid()
{
    if(pck.length()!=5)
        return false;
    int temp = pck.at(4);
    temp ^= 0xFF;
    temp &= 0xFF;
    if(temp!=(int)pck.at(0))
        return false;
    return true;
}

QString FrameSG1::toQString()
{
    if(!isValid())
        return InvalidString();

    if((pck[0]&0xF0)==0x10)
        return QString("Odczyt zmiennej kalibracjyjnej nr. ")+toShortQString();
    if((pck[0]&0xF0)==0x00)
        return QString("Żądanie odczytu zmiennej kalibracjyjnej nr. ")+toShortQString();
    if((pck[0]&0xF0)==0x20)
        return QString("Żądanie zapisu zmiennej kalibracjyjnej nr. ")+toShortQString();

    switch (pck.at(0))
    {
    case 'c':                           //Pomiar
        return QString("Zapytanie o zliczenia");
    case 'C':                           //Pomiar
        return QString("Raport: pomiar: ")+toShortQString();
    case 'A':                           //Licznik kalibracji
        return QString("Raport: pomiar autokalibracji: ")+toShortQString();
    case 't':                           //Temperatura
        return QString("Zapytanie o temperature");
    case 'T':                           //Temperatura
        return QString("Raport: temperatura: ")+toShortQString();
    case 'z':                           //Zatkanie
        return QString("Zapytanie o zatkanie.");
    case 'Z':                           //Zatkanie
        return QString("Raport: pomiar zatkania: ")+toShortQString();
    case 'l':                           //Poziomy
        return QString("Zapytanie o poziomy.");
    case 'L':                           //Poziomy
        return QString("Raport: poziomy progów: ")+toShortQString();
    case 'd':                           //Napięcie SiPM
        return QString("Zapytanie o napięcie SiPM.");
    case 'D':                           //Napięcie SiPM
        return QString("Raport: napięcie SiPM: ")+toShortQString();
    case 'h':                           //Hello
        return QString("Zapytanie hello.");
    case 'H':                           //Hello
        return QString("Hello: ")+toShortQString();
    case 'B':                           //Zatkanie bufora
        return QString("Raport: zatkanie bufora odczytu!");
    case 'v':                           //Napięcie baterii
        return QString("Zapytanie o napięcie baterii.");
    case 'V':                           //Napięcie baterii
        return QString("Napięcie zasilania: ")+toShortQString();
    case 'a':                           //Autokalibracja
        return QString("Wymuszenie autokalibracji.");
    case 'r':                           //Reset
        return QString("Wymuszenie resetu.");
    case 's':                           //Konfiguracja autoraportów
        return QString("Zapis konfiguracji automatycznych raportów: ")+toShortQString();
    case 'E':                           //Error
        return QString("Błąd urządzenia: ")+toShortQString();
    case 'e':                           //Wymuszenie napięcia SiPM
        return QString("Wymuszenie napięcia SiPM: ")+toShortQString();
    }

    QString temp;
    for(auto s: pck)
        temp.append(QString("0x%1 ").arg((int)(s)&0xFF, 2, 16, QChar('0')));
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
        tempi &= 0xFF;
        if(tempi!=(int)pck.at(0))
            return "Niezgodność nagłówka i dopełnienia: " + temohex;
    }

    return "Nieznany nagłówek: " + temohex;
}

QString FrameSG1::toShortQString()
{
    if(!isValid())
        return "XXX";

    const float k = 3.3*(620.0+4700.0)/(620.0)/256, kb=3.3/1024.0;
    float voltage;
    int result, mlv=0, llv=0, pga, pgb, pra, prb;
    QString pgt, prt;

    result = 0;
    result |= (pck[1]<<16)&0xFF0000;
    result |= (pck[2]<<8)&0xFF00;
    result |= pck[3]&0xFF;

    int calNr = pck[0]&0x0F;
    if((pck[0]&0xF0)==0x10)
        return QString("%1: %2").arg(calNr, 2, 10).arg(result, 8, 10);
    if((pck[0]&0xF0)==0x00)
        return QString("%1").arg(calNr, 2, 10);
    if((pck[0]&0xF0)==0x20)
        return QString("%1: %2").arg(calNr, 2, 10).arg(result, 8, 10);

    switch (pck.at(0))
    {
    case 'C':                           //Pomiar
        result /= timeres;
        return QString("%1 imp/s").arg(result, 8, 10);
    case 'A':                           //Licznik kalibracji
        return QString("%1 imp").arg(result, 8, 10);
    case 'T':                           //Temperatura
        return QString("%1 ADC").arg(result, 8, 10);
    case 'Z':                           //Zatkanie
        return QString("%1 ADC").arg(result, 8, 10);
    case 'L':                           //Poziomy
        mlv=0;
        llv=0;
        mlv |= pck[2]&0xFF;
        llv |= pck[3]&0xFF;
        llv = 8-llv;
        return QString("%1/%2").arg(mlv, 0, 10).arg(llv, 0, 10);
    case 'D':                           //Napięcie SiPM
        voltage = (float)result*k;
        return QString("%1 DAC, ~").arg(result, 0, 10) +QString::number(voltage, 'f', 2)+" V";
    case 'e':                           //Wymuszenie napięcia SiPM
        voltage = (float)result*k;
        return QString("%1 DAC, ~").arg(result, 0, 10) +QString::number(voltage, 'f', 2)+" V";
    case 'H':                           //Hello
        pga=0;
        pga=(pck[3]>>4)&0x07;
        pgb=0;
        pgb=(pck[3]&0x0F);
        pra=0;
        pra=(pck[2]>>4)&0x07;
        prb=0;
        prb=(pck[2]&0x0F);
        pgt = "";
        prt = "";
        if(pck[3]&0x80)
            pgt="t";
        if(pck[2]&0x80)
            prt="t";
        return QString("prog. v%1.%2").arg(pga, 0, 10).arg(pgb, 0, 10)+pgt+QString(", prot. v%1.%2").arg(pra, 0, 10).arg(prb, 0, 10)+prt+".";
    case 'V':                           //Napięcie baterii
        voltage = (float)result*kb;
        return QString("%1 ADC, ~").arg(result, 0, 10) +QString::number(voltage, 'f', 2)+" V";
    case 's':                           //Zapis autoraportów
        return QString("0x%1 ").arg((int)(result&0xFF), 2, 16, QChar('0')).toUpper().replace("X", "x");
    case 'E':                           //Error
        voltage = (float)result*k;
        return QString("0x%1 - ").arg((int)(pck[3]&0xFF), 2, 16, QChar('0')).toUpper().replace("X", "x")+errorNumbers.value(pck.at(3), "Nieznany błąd");
    }

    return "XXX";
}

QByteArray FrameSG1::magicNumbers()
{
    if(pck.length()>0)
        return pck.left(1);
    else
        return QByteArray();
}

float FrameSG1::TimeRes()
{
    return timeres;
}
