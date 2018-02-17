#ifndef FRAMEPAZUR_HPP
#define FRAMEPAZUR_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FramePazur : public Frame
{
public:
    FramePazur(QByteArray ba);
    ~FramePazur(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

private:
    bool isHeaderOk();

    QString dispHeader();
};

#endif
