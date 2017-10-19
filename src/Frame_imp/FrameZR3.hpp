#ifndef FRAMEZR3_HPP
#define FRAMEZR3_HPP

#include <QByteArray>
#include <QMap>
#include "../Frame.hpp"

class FrameZR3 : public Frame
{
public:
    FrameZR3(QByteArray ba);
    ~FrameZR3(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

    static void AppendLRC(QByteArray& ba);
    static bool CheckLRC(QByteArray &ba);
    static char CalcLRC(QByteArray ba);

protected:
    QString invalidDesc;

    QMap<int, QString> protErrorNumbers;

    QString DirectString();
    QString ProtString();
    QString AplString();

    static const char protHOLLOW = 0x00;
    static const char protHELLO = 0x01;
    static const char protSET_ADR = 0x02;
    static const char protSET_NEXT_ADR = 0x03;
    static const char protDATA = 0x04;
};

#endif
