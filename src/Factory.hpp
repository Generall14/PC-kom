#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QByteArray>
#include <QFrame>
#include "Frame.hpp"
#include "MediumUI.hpp"
#include "Mendium.hpp"

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

    enum mendiumFormat
    {
        mendiumNone,
        mendiumEmpty,
        mendiumRS
    };

    static void Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, QString name = "Komunikator SG-2");

    static Frame* newFrame(QByteArray ba);
    static MediumUI* newMediumUI(QFrame *fr);
    static Mendium* newMendium();

    static QString WindowName();

    static int readTimeout(); // ???????????????????
    static int writeTimeout(); // ??????????????????
    static int frameLength(); // ???????????????????

private:
    static frameFormat frame;
    static mediumUiFormat mediumui;
    static mendiumFormat mendium;
    static QString windowName;
};

#endif
