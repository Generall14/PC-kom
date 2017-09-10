#include "Factory.hpp"

#include "Frame_imp/FrameEmpty.hpp"
#include "Frame_imp/FrameTransparent.hpp"
#include "Frame_imp/FrameSG1.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"
#include "Mendium_imp/MendiumFakeSG1.hpp"

#include "LogicUI_imp/LogicUIEmpty.hpp"
#include "LogicUI_imp/LogicUISG-1.hpp"

#include "FrameBuilder_imp/FrameBuilderEmpty.hpp"
#include "FrameBuilder_imp/FrameBuilderSG1.hpp"

#include "LogUI_imp/LogUIEmpty.hpp"
#include "LogUI_imp/LogUITerm.hpp"

Factory::frameFormat Factory::frame = Factory::frameEmpty;
Factory::mediumUiFormat Factory::mediumui = Factory::mediumUIEmpty;
Factory::mendiumFormat Factory::mendium = Factory::mendiumEmpty;
Factory::logicUiFormat Factory::logicUi = Factory::logicUiEmpty;
Factory::frameBuilderFormat Factory::frameBuilder = Factory::frameBuilderEmpty;
Factory::logUIFormat Factory::logUI = Factory::logUIEmpty;
QString Factory::windowName = "XXX";
QString Factory::icoPath = "ikona.ico";

void Factory::Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, logicUiFormat lui, frameBuilderFormat fb, logUIFormat lgui, QString name, QString ico)
{
    Factory::frame = ff;
    Factory::mediumui = muif;
    Factory::mendium = mf;
    Factory::windowName = name;
    Factory::logicUi = lui;
    Factory::frameBuilder = fb;
    Factory::logUI = lgui;
    Factory::icoPath = ico;
}

Frame* Factory::newFrame(QByteArray ba)
{
    switch (frame)
    {
    case Factory::frameNone:
        return NULL;
    case Factory::frameEmpty:
        return new FrameEmpty(ba);
    case Factory::frameTransparent:
        return new FrameTransparent(ba);
    case Factory::frameSG1:
        return new FrameSG1(ba);
    }
    return NULL;
}

MediumUI* Factory::newMediumUI(QFrame *fr)
{
    switch (mediumui)
    {
    case Factory::mediumUINone:
        return NULL;
    case Factory::mediumUIEmpty:
        return new MediumUiEmpty(fr);
    case Factory::mediumUIRS:
        return new MediumUiRS(fr);
    }
    return NULL;
}

LogicUI* Factory::newLogicUI(QFrame *fr)
{
    switch (logicUi)
    {
    case Factory::logicUiNone:
        return NULL;
    case Factory::logicUiEmpty:
        return new LogicUIEmpty(fr);
    case Factory::logicUiSG1:
        return new LogicUISG1(fr);
    }
    return NULL;
}

Mendium* Factory::newMendium()
{
    switch (mendium)
    {
    case Factory::mendiumNone:
        return NULL;
    case Factory::mendiumEmpty:
        return new MendiumEmpty();
    case Factory::mendiumRS:
        return new MendiumRS();
    case Factory::mendiumFakeGS1:
        return new MendiumFakeSG1();
    }
    return NULL;
}

FrameBuilder* Factory::newFrameBuilder()
{
    switch (frameBuilder)
    {
    case frameBuilderNone:
        return NULL;
    case frameBuilderEmpty:
        return new FrameBuilderEmpty;
    case frameBuilderSG1:
        return new FrameBuilderSG1;
    }
    return NULL;
}

LogUI* Factory::newLogUI(QFrame* fr)
{
    switch (logUI)
    {
    case logUINone:
        return NULL;
    case logUIEmpty:
        return new LogUIEmpty(fr);
    case logUITerm:
        return new LogUITerm(fr);
    }
    return NULL;
}

QString Factory::WindowName()
{
    return windowName;
}

QString Factory::IcoPath()
{
    return icoPath;
}
