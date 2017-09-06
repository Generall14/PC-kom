#ifndef FRAMETRANSPARENT_HPP
#define FRAMETRANSPARENT_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FrameTransparent : public Frame
{
public:
    FrameTransparent(QByteArray ba);
    ~FrameTransparent(){}

    virtual bool isValid();
    virtual QString toQString();
};

#endif
