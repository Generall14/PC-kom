#ifndef FRAMESTAWROV_HPP
#define FRAMESTAWROV_HPP

#include <QByteArray>
#include <QTimer>
#include <QMap>
#include "../Frame.hpp"

class FrameStawrov : public Frame
{
public:
    FrameStawrov(QByteArray ba);
    ~FrameStawrov(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

    static QByteArray AddCRC16(QByteArray data);
    static bool CheckCRC16(Frame* fr);

protected:
    QString InvalidString();
    QString errorString;
};

#endif
