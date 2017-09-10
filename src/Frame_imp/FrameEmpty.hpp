#ifndef FRAMEEMPTY_HPP
#define FRAMEEMPTY_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FrameEmpty : public Frame
{
public:
    FrameEmpty(QByteArray ba);
    ~FrameEmpty(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
};

#endif
