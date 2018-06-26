#ifndef PUREMESSAGEZR3IIC_HPP
#define PUREMESSAGEZR3IIC_HPP

#include <QByteArray>
#include <QString>
#include <QByteArray>

class PureMessageZR3IIC
{
public:
    static QString desc(QByteArray _arr);

    static QByteArray slaveTEST();
    static QByteArray slaveRST();
    static QByteArray slaveRDSECTION(uint nr);
    static QByteArray slaveWRSECTION(uint nr, QByteArray data);

    static const uchar masterTEST_c = 0xFF;
    static const uchar masterRDSECTIONo_c = 0x81;

    static const uchar slaveTEST_c = 0x7F;
    static const uchar slaveRST_c = 0x00;
    static const uchar slaveRDSECTION_c = 0x01;
    static const uchar slaveWRSECTION_c = 0x02;

private:
    PureMessageZR3IIC(){}
    static QByteArray appendSize(QByteArray dat);
};

#endif
