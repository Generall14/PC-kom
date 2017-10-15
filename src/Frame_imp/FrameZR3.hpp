#ifndef FRAMEZR3_HPP
#define FRAMEZR3_HPP

#include <QByteArray>
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
};

#endif
