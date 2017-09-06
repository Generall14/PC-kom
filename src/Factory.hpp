#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QByteArray>
#include <QFrame>
#include "Frame.hpp"
#include "MediumUI.hpp"
#include "Mendium.hpp"
#include "LogicUI.hpp"

class Factory
{
    Factory(){}
public:
    enum frameFormat
    {
        frameNone,
        frameEmpty,
        frameTransparent,
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

    enum logicUiFormat
    {
        logicUiNone,
        logicUiEmpty
    };

    static void Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, logicUiFormat lui, QString name = "Komunikator SG-2");

    static Frame* newFrame(QByteArray ba);
    static MediumUI* newMediumUI(QFrame *fr);
    static Mendium* newMendium();
    static LogicUI* newLogicUI(QFrame *fr);

    static QString WindowName();

private:
    static frameFormat frame;
    static mediumUiFormat mediumui;
    static mendiumFormat mendium;
    static logicUiFormat logicUi;
    static QString windowName;
};

#endif
