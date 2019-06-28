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
    static QByteArray slaveWRSECTION(uint nr, const QByteArray& data);
    static QByteArray slaveCALL();
    static QByteArray slavePALSY();
    static QByteArray slaveGET_DBG_DAT();
    static QByteArray slaveRST_HIST();
    static QByteArray slaveGET_HIST();
    static QByteArray slaveMES_RST(uint16_t D);

    static const uchar masterTEST_c = 0xFF;
    static const uchar masterRDSECTIONo_c = 0x81;
    static const uchar masterMES = 0x84;
    static const uchar masterRET_c = 0x85;
    static const uchar masterDBG_c = 0x86;
    static const uchar masterHIST_c = 0x87;

    static const uchar slaveTEST_c = 0x7F;
    static const uchar slaveRST_c = 0x00;
    static const uchar slaveRDSECTION_c = 0x01;
    static const uchar slaveWRSECTION_c = 0x02;
    static const uchar slaveCALL_c = 0x03;
    static const uchar slaveMES_RST_c = 0x04;
    static const uchar slavePALSY_c = 0x05;
    static const uchar slaveGET_DBG_DAT_c = 0x07;
    static const uchar slaveRST_HIST_c = 0x08;
    static const uchar slaveGET_HIST_c = 0x09;

    static QString getWho(char b, QString temp);

private:
    PureMessageZR3IIC(){}
    static QByteArray appendSize(QByteArray dat);
};

#endif
