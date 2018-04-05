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

    static QByteArray wkpSTORE();

private:
    QByteArray _arr;

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

};

#endif
