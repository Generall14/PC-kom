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
    static QByteArray wiWRSECTION_dev(uint nr, bool prot, uint16_t magic, QByteArray data);
private:
    QByteArray _arr;

    static const uchar wiRDCONST_c = 0x00;
    static const uchar wiRDCONSTo_c = 0x01;
    static const uchar wiRDSECTION_c = 0x02;
    static const uchar wiRDSECTIONo_c = 0x03;
    static const uchar wiWRSECTION_c = 0x04;
};

#endif
