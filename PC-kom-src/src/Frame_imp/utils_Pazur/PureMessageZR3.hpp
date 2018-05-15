#ifndef PUREMESSAGEZR3_HPP
#define PUREMESSAGEZR3_HPP

#include <QByteArray>
#include <QString>
#include <QByteArray>

class PureMessageZR3
{
public:
    static QString desc(QByteArray _arr, bool* found=nullptr);

    static QByteArray techREQ(uint16_t magic);
    static QByteArray techACC(uint16_t magic, uint16_t rnd);
    static QByteArray techRDSECTION(uint nr);
    static QByteArray techWRSECTION(uint nr, uint16_t magic, QByteArray data);
    static QByteArray techRESET();

    static QByteArray zr3ReadDose();
    static QByteArray zr3SetDose(float dose);
    static QByteArray zr3ReadDoseRate();
    static QByteArray zr3ReadDoseRateProbe();
    static QByteArray zr3RstDoseRateProbe();
    static QByteArray zr3ReadEstimatedEnergy();
    static QByteArray zr3ReadEstimatedNeutronB();
    static QByteArray zr3ReadEstimatedGammaDoseRate();
    static QByteArray zr3RstEstimatedEnergyProbe();
    static QByteArray zr3ReadEstimatedEnergyProbe();
    static QByteArray zr3RstEstimatedNeutronBProbe();
    static QByteArray zr3ReadEstimatedNeutronBProbe();
    static QByteArray zr3RstEstimatedGammaDoseRateProbe();
    static QByteArray zr3ReadEstimatedGammaDoseRateProbe();

private:
    PureMessageZR3(){}

    static const uchar techREQ_c = 0x00;
    static const uchar techINV_c = 0x01;
    static const uchar techACC_c = 0x02;
    static const uchar techCONF_c = 0x03;
    static const uchar techRDSECTION_c = 0x3F;
    static const uchar techRDSECTIONo_c = 0x3E;
    static const uchar techWRSECTION_c = 0x3D;
    static const uchar techRESET_c = 0x3C;
};

#endif
