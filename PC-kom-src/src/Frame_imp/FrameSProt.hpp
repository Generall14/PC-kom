#ifndef FRAMESPROT_HPP
#define FRAMESPROT_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FrameSProt : public Frame
{
public:
    FrameSProt(QByteArray ba);
    FrameSProt(uint16_t cmd, QByteArray data);
    ~FrameSProt(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();
};

#endif
