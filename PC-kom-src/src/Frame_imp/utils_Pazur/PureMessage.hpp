#ifndef PUREMESSAGE_HPP
#define PUREMESSAGE_HPP

#include <QByteArray>
#include <QString>
#include <QByteArray>

class PureMessage
{
public:
    PureMessage(QByteArray arr); // pelen zakres danych (adres i rozmiar tez)

    QString desc() const;

    static QByteArray wiRDCONST(uint offset); // same dane wlasciwe (bez bajtow adresu i rozmiaru)
    static QByteArray wiRDSECTION_dev(uint nr, bool prot);
    static QByteArray wiRDSECTION_long(QByteArray nr);
    static QByteArray wiWRSECTION_dev(uint nr, bool prot, uint16_t magic, QByteArray data);
    static QByteArray wiWRSECTION_long(QByteArray nr, uint16_t magic, QByteArray data);
    static QByteArray wiGFDA(bool utkak, QByteArray nr);

    static QByteArray wiRdAU();
    static QByteArray wiRdOTOPG();
    static QByteArray wiRdBOCW();
    static QByteArray wiRdANWP();
    static QByteArray wiRdBOPG();
    static QByteArray wiRdBSPPG();
    static QByteArray wiRdBMP();
    static QByteArray wiRdBARP();

    static QByteArray wiWrAU(uint16_t magic, uchar adr);
    static QByteArray wiWrOTOPG(uint16_t magic, uint16_t tempo);
    static QByteArray wiWrBOCW(uint16_t magic, bool lock);
    static QByteArray wiWrANWP(uint16_t magic, uchar adr);
    static QByteArray wiWrBOPG(uint16_t magic, bool lock);
    static QByteArray wiWrBSPPG(uint16_t magic, bool lock);
    static QByteArray wiWrBMP(uint16_t magic, bool lock);
    static QByteArray wiWrBARP(uint16_t magic, bool lock);

    static QByteArray wkpSTORE();
    static QByteArray wkpCONNECT();
    static QByteArray wkpCONNECTo(QByteArray next);
    static QByteArray wkpBUILD();
    static QByteArray wkpBUILDo();
    static QByteArray wkpRESET();

    static uint calcMagicNumber(QByteArray wID_IDX);

    static const uchar wiRDCONST_c = 0x00;
    static const uchar wiRDCONSTo_c = 0x01;
    static const uchar wiRDSECTION_c = 0x02;
    static const uchar wiRDSECTIONo_c = 0x03;
    static const uchar wiWRSECTION_c = 0x04;
    static const uchar wiGFDA_c = 0x05;
    static const uchar wiGFDAo_c = 0x06;
    static const uchar wiWARN_c = 0x07;
    static const uchar wiFAULT_c = 0x08;
    static const uchar wiSERVICE_c = 0x09;

    static const uchar wkpSTORE_c = 0x02;
    static const uchar wkpCONNECT_c = 0x03;
    static const uchar wkpCONNECTo_c = 0x13;
    static const uchar wkpBUILD_c = 0x04;
    static const uchar wkpBUILDo_c = 0x14;
    static const uchar wkpRESET_c = 0x05;

private:
    QByteArray _arr;
};

#endif
