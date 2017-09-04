#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QByteArray>
#include <QFrame>
#include "Frame.hpp"
#include "MediumUI.hpp"

class Factory
{
    Factory(){}
public:
    enum frameFormat
    {
        frameNone,
        frameEmpty,
        frameSG1
    };

    enum mediumUiFormat
    {
        mediumUINone,
        mediumUIEmpty,
        mediumUIRS
    };

    static void Config(frameFormat ff, mediumUiFormat muif, QString name = "Komunikator SG-2");

    static Frame* newFrame(QByteArray ba);
    static MediumUI* newMediumUI(QFrame *fr);

    static QString WindowName();

    static int readTimeout();
    static int writeTimeout();
    static int frameLength();

private:
    static frameFormat frame;
    static mediumUiFormat mediumui;
    static QString windowName;
};

#endif
