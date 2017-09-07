#include "Factory.hpp"

#include "Frame_imp/FrameEmpty.hpp"
#include "Frame_imp/FrameTransparent.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"

#include "LogicUI_imp/LogicUIEmpty.hpp"

Factory::frameFormat Factory::frame = Factory::frameEmpty;
Factory::mediumUiFormat Factory::mediumui = Factory::mediumUIEmpty;
Factory::mendiumFormat Factory::mendium = Factory::mendiumEmpty;
Factory::logicUiFormat Factory::logicUi = Factory::logicUiNone;
QString Factory::windowName = "XXX";

void Factory::Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, logicUiFormat lui, QString name)
{
    Factory::frame = ff;
    Factory::mediumui = muif;
    Factory::mendium = mf;
    Factory::windowName = name;
    Factory::logicUi = lui;
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
        return NULL;//-----------------------------------------------
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
    }
    return NULL;
}

QString Factory::WindowName()
{
    return windowName;
}
