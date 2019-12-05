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
    static const uint16_t CMD_GETSEC = 0x101;
    static const uint16_t CMD_REGETSEC = 0x001;
    static const uint16_t CMD_SETSEC = 0x102;
    static const uint16_t CMD_RESETSEC = 0x002;

    QString printSection(uint8_t num, QByteArray data, uint16_t offset);
    static const uint8_t SEC_TESTSEC = 0x00;
    static const uint8_t SEC_SYSTIME = 0x01;
};

#endif
