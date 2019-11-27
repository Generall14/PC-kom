#ifndef FRAMESPROT_HPP
#define FRAMESPROT_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FrameSProt : public Frame
{
public:
    FrameSProt(QByteArray ba);
    FrameSProt(uint16_t cmd, QByteArray data=QByteArray());
    ~FrameSProt(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

    uint16_t cmd();
    uint8_t bytes();
    QByteArray package();

    static QSharedPointer<Frame> hello();

private:
    bool valid = false;
    bool validated = false;

    static const uint16_t CMD_HELLO = 0x100;
    static const uint16_t CMD_RHELLO = 0x000;
};

#endif
