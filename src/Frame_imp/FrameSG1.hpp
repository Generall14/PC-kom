#ifndef FRAMESG1_HPP
#define FRAMESG1_HPP

#include <QByteArray>
#include <QTimer>
#include "../Frame.hpp"

class FrameSG1 : public Frame
{
public:
    FrameSG1(QByteArray ba);
    ~FrameSG1(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

protected:
    QString InvalidString();
};

#endif
