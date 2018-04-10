#ifndef PUREMESSAGEZR3_HPP
#define PUREMESSAGEZR3_HPP

#include <QByteArray>
#include <QString>
#include <QByteArray>

class PureMessageZR3
{
public:
    static QString desc(QByteArray _arr, bool* found=nullptr);

//    static QByteArray wiRDCONST(uint offset); // same dane wlasciwe (bez bajtow adresu i rozmiaru)
//    static QByteArray wiRDSECTION_dev(uint nr, bool prot);
//    static QByteArray wiRDSECTION_long(QByteArray nr);
//    static QByteArray wiWRSECTION_dev(uint nr, bool prot, uint16_t magic, QByteArray data);
//    static QByteArray wiWRSECTION_long(QByteArray nr, uint16_t magic, QByteArray data);
//    static QByteArray wiGFDA(bool utkak, QByteArray nr);
    static QByteArray techREQ(uint16_t magic);

//    static QByteArray wkpSTORE();
//    static QByteArray wkpCONNECT();
//    static QByteArray wkpCONNECTo(QByteArray next);
//    static QByteArray wkpBUILD();
//    static QByteArray wkpBUILDo();
//    static QByteArray wkpRESET();

private:
    PureMessageZR3(){}

    static const uchar techREQ_c = 0x00;
//    static const uchar wiRDCONSTo_c = 0x01;
//    static const uchar wiRDSECTION_c = 0x02;
//    static const uchar wiRDSECTIONo_c = 0x03;
//    static const uchar wiWRSECTION_c = 0x04;
//    static const uchar wiGFDA_c = 0x05;
//    static const uchar wiGFDAo_c = 0x06;
//    static const uchar wiWARN_c = 0x07;
//    static const uchar wiFAULT_c = 0x08;
//    static const uchar wiSERVICE_c = 0x09;

//    static const uchar wkpSTORE_c = 0x02;
//    static const uchar wkpCONNECT_c = 0x03;
//    static const uchar wkpCONNECTo_c = 0x13;
//    static const uchar wkpBUILD_c = 0x04;
//    static const uchar wkpBUILDo_c = 0x14;
//    static const uchar wkpRESET_c = 0x05;
};

#endif
