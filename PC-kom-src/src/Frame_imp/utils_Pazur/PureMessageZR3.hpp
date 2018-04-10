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

private:
    PureMessageZR3(){}

    static const uchar techREQ_c = 0x00;
    static const uchar techINV_c = 0x01;
    static const uchar techACC_c = 0x02;
};

#endif
