#ifndef FRAMETRANSPARENT_HPP
#define FRAMETRANSPARENT_HPP

#include <QByteArray>
#include "../Frame.hpp"

class FrameTransparent : public Frame
{
public:
    FrameTransparent(QByteArray ba);
    ~FrameTransparent(){}

    enum displayMethod
    {
        ascii=0,
        hex=1,
        mixed=2
    };

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

    static displayMethod getDisplayMethod();
    static char getInvalidAsciiSign();
    static char getHexSpecifier();
    static void setDisplayMethod(displayMethod _method);
    static void setInvalidAsciiSign(char _sign);
    static char setHexSpecifier(char _sign);

private:
    static displayMethod _displayMethod;
    static char _invalidAsciiSign;
    static char _hexSpecifier;
};

#endif
