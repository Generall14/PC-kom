#include "PureMessageZR3.hpp"
#include <cassert>
#include <QDebug>
#include "src/Utils/StaticUtils.hpp"

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
        case techRESET_c:
        {
            if(_arr.size()!=3)
                break;
            temp.append(QString("techRESET"));
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

QByteArray PureMessageZR3::techRESET()
{
    QByteArray temp;
    temp.append(techRESET_c);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadDose()
{
    QByteArray temp;
    temp.append(0x21);
    temp.append(0x04);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedEnergy()
{
    QByteArray temp;
    temp.append(0x21);
    temp.append(0x15);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedNeutronB()
{
    QByteArray temp;
    temp.append(0x21);
    temp.append(0x05);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedGammaDoseRate()
{
    QByteArray temp;
    temp.append(0xA1);
    temp.append(0x20);
    temp.append(0x02);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadDoseRate()
{
    QByteArray temp;
    temp.append(0x21);
    temp.append(0x02);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadAlarmState()
{
    QByteArray temp;
    temp.append(0x34);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadDoseRateProbe()
{
    QByteArray temp;
    temp.append(0x71);
    return temp;
}

QByteArray PureMessageZR3::zr3RstDoseRateProbe()
{
    QByteArray temp;
    temp.append(0x72);
    return temp;
}

QByteArray PureMessageZR3::zr3SetDose(float dose)
{
    QByteArray temp;
    temp.append(0x22);
    temp.append(0x04);
    temp.append(SU::float322ByteArray(dose));
    return temp;
}

QByteArray PureMessageZR3::zr3RstEstimatedEnergyProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x22);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedEnergyProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x21);
    return temp;
}

QByteArray PureMessageZR3::zr3RstEstimatedNeutronBProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x42);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedNeutronBProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x41);
    return temp;
}

QByteArray PureMessageZR3::zr3RstEstimatedGammaDoseRateProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x22);
    return temp;
}

QByteArray PureMessageZR3::zr3ReadEstimatedGammaDoseRateProbe()
{
    QByteArray temp;
    temp.append(0xF0);
    temp.append(0x21);
    return temp;
}

QByteArray PureMessageZR3::zr3ForceDoseRate(bool toAdres)
{
    QByteArray temp;
    temp.append(0x10);
    if(toAdres)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray PureMessageZR3::zr3ForceDose(bool toAdres)
{
    QByteArray temp;
    temp.append(0x90);
    temp.append(0x20);
    if(toAdres)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray PureMessageZR3::zr3ForceEsts(bool toAdres)
{
    QByteArray temp;
    temp.append(0x90);
    temp.append(0x60);
    if(toAdres)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray PureMessageZR3::zr3ForceAlarmState(bool toAdres)
{
    QByteArray temp;
    temp.append(0x90);
    temp.append(0x40);
    if(toAdres)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray PureMessageZR3::zr3ForceWyAlarm(bool toAdres)
{
    QByteArray temp;
    temp.append(0x90);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x04);
    if(toAdres)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAutoDoseRate(uint16_t magic, uint16_t ms, bool en, uchar adr)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x10);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    temp.append(ms&0xFF);
    temp.append((ms>>8)&0xFF);
    temp.append(adr&0x3F);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAutoDose(uint16_t magic, uint16_t ms, bool en, uchar adr)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x90);
    temp.append(0x20);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    temp.append(ms&0xFF);
    temp.append((ms>>8)&0xFF);
    temp.append(adr&0x3F);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAutoEst(uint16_t magic, uint16_t ms, bool en, uchar adr)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x90);
    temp.append(0x60);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    temp.append(ms&0xFF);
    temp.append((ms>>8)&0xFF);
    temp.append(adr&0x3F);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAutoAlarmState(uint16_t magic, uint16_t ms, bool en, uchar adr)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x90);
    temp.append(0x40);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    temp.append(ms&0xFF);
    temp.append((ms>>8)&0xFF);
    temp.append(adr&0x3F);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAutoWyAlarm(uint16_t magic, uint16_t ms, bool en, uchar adr)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x90);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x80);
    temp.append(0x04);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);
    temp.append(ms&0xFF);
    temp.append((ms>>8)&0xFF);
    temp.append(adr&0x3F);
    return temp;
}

QByteArray PureMessageZR3::zr3SetAlarmStateDir(uint16_t magic, bool dir)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x30);

    if(dir)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmEnable(uint16_t magic, bool en)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x50);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmSetMode(uint16_t magic, uint min, uint max, uint mod, uint tmin)
{
    min &= 0x03;
    max &= 0x03;
    mod &= 0x03;

    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x51);

    uchar tt = 0x00;
    tt |= min;
    tt |= max<<2;
    tt |= mod<<4;

    temp.append(tt&0xFF);
    temp.append(tmin&0xFF);

    return temp;
}

QByteArray PureMessageZR3::zr3SetAlarmStateUwag(uint16_t magic, bool en, float thr, uint prze, uint utrz)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x31);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    temp.append(SU::float322ByteArray(thr));
    temp.append(utrz&0xFF);
    temp.append(prze&0xFF);

    return temp;
}

QByteArray PureMessageZR3::zr3SetAlarmStateNieb(uint16_t magic, bool en, float thr, uint prze, uint utrz)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x32);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    temp.append(SU::float322ByteArray(thr));
    temp.append(utrz&0xFF);
    temp.append(prze&0xFF);

    return temp;
}

QByteArray PureMessageZR3::zr3SetAlarmStateZagr(uint16_t magic, bool en, float thr, uint prze, uint utrz)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x33);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    temp.append(SU::float322ByteArray(thr));
    temp.append(utrz&0xFF);
    temp.append(prze&0xFF);

    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmKontrolaEn(uint16_t magic, bool en)
{
    QByteArray temp;
    temp.append(0x04);
    temp.append(magic&0xFF);
    temp.append((magic>>8)&0xFF);

    temp.append(0x52);

    if(en)
        temp.append(0x01);
    else
        temp.append((char)0x00);

    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmTest()
{
    QByteArray temp;
    temp.append(0x55);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmEndTest()
{
    QByteArray temp;
    temp.append(0x56);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmBlokuj()
{
    QByteArray temp;
    temp.append(0x53);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmOdblokuj()
{
    QByteArray temp;
    temp.append(0x54);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmSymuluj(uint lvl)
{
    QByteArray temp;
    temp.append(0x57);
    temp.append(lvl&0x03);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmKoniecSymulacji()
{
    QByteArray temp;
    temp.append(0x58);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmPotwierdz()
{
    QByteArray temp;
    temp.append(0x52);
    return temp;
}

QByteArray PureMessageZR3::zr3WyAlarmOdczytaj()
{
    QByteArray temp;
    temp.append(0x51);
    return temp;
}
