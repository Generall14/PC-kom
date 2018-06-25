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

private:
    PureMessageZR3IIC(){}
    static QByteArray appendSize(QByteArray dat);

    static const uchar masterTEST_c = 0xFF;

    static const uchar slaveTEST_c = 0x7F;
    static const uchar slaveRST_c = 0x00;
};

#endif
