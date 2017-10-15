#include "Factory.hpp"

#include "Frame_imp/FrameEmpty.hpp"
#include "Frame_imp/FrameTransparent.hpp"
#include "Frame_imp/FrameSG1.hpp"
#include "Frame_imp/FrameStawrov.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"
#include "Mendium_imp/MendiumFakeSG1.hpp"
#include "Mendium_imp/MendiumFakeStawrow.hpp"

#include "LogicUI_imp/LogicUIEmpty.hpp"
#include "LogicUI_imp/LogicUISG-1.hpp"
#include "LogicUI_imp/LogicUIStawrov.hpp"

#include "FrameBuilder_imp/FrameBuilderEmpty.hpp"
#include "FrameBuilder_imp/FrameBuilderSG1.hpp"
#include "FrameBuilder_imp/FrameBuilderStawrov.hpp"

#include "LogUI_imp/LogUIEmpty.hpp"
#include "LogUI_imp/LogUITerm.hpp"

#include "LogFile_imp/LogFileEmpty.hpp"
#include "LogFile_imp/LogFileDefault.hpp"

#include "LogFormater_imp/LogFormaterEmpty.hpp"
#include "LogFormater_imp/LogFormaterHtml.hpp"

Factory::frameFormat Factory::frame = Factory::frameEmpty;
Factory::mediumUiFormat Factory::mediumui = Factory::mediumUIEmpty;
Factory::mendiumFormat Factory::mendium = Factory::mendiumEmpty;
Factory::logicUiFormat Factory::logicUi = Factory::logicUiEmpty;
Factory::frameBuilderFormat Factory::frameBuilder = Factory::frameBuilderEmpty;
Factory::logUIFormat Factory::logUI = Factory::logUIEmpty;
Factory::logFileFormat Factory::logFile = Factory::logFileEmpty;
Factory::logFormaterFormat Factory::logFormater = Factory::logFormaterEmpty;
QString Factory::windowName = "XXX";
QString Factory::icoPath = "ikona.ico";

/**
 * Funkcja służy do określenia które konkretne implementacje będą zwracane w metodach fabryki abstrakcyjnej. Dodatkowo wskazuje nazwę dla głównego okna programu
 * i adres do ikony.
 */
void Factory::Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, logicUiFormat lui, frameBuilderFormat fb, logUIFormat lgui, \
                     logFileFormat lff, logFormaterFormat lf, QString name, QString ico)
{
    Factory::frame = ff;
    Factory::mediumui = muif;
    Factory::mendium = mf;
    Factory::windowName = name;
    Factory::logicUi = lui;
    Factory::frameBuilder = fb;
    Factory::logUI = lgui;
    Factory::icoPath = ico;
    Factory::logFile = lff;
    Factory::logFormater = lf;
}

/**
 * Zwraca obiekt pochodny po Frame w zależności od konfiguracji frameFormat.
 * @param ba - dane dla obiektu Frame.
 */
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
    case Factory::frameStawrov:
        return new FrameStawrov(ba);
    }
    return NULL;
}

/**
 * Zwraca obiekt pochodny po MediumUI w zależności od konfiguracji mediumUiFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
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

/**
 * Zwraca obiekt pochodny po LogicUI w zależności od konfiguracji logicUiFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
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
    case Factory::logicUIStawrov:
        return new LogicUIStawrov(fr);
    }
    return NULL;
}

/**
 * Zwraca obiekt pochodny po Mendium w zależności od konfiguracji mendiumFormat.
 */
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
    case Factory::mendiumFakeStawrow:
        return new MendiumFakeStawrow();
    }
    return NULL;
}

/**
 * Zwraca obiekt pochodny po FrameBuilder w zależności od konfiguracji frameBuilderFormat.
 */
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
    case frameBuilderStawrov:
        return new FrameBuilderStawrov;
    }
    return NULL;
}

/**
 * Zwraca obiekt pochodny po LogUI w zależności od konfiguracji logUIFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
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

/**
 * Zwraca obiekt pochodny po LogFile w zależności od konfiguracji logFileFormat.
 */
LogFile* Factory::newLogFile()
{
    switch (logFile)
    {
    case logFileNone:
        return NULL;
    case logFileEmpty:
        return new LogFileEmpty();
    case logFileDefault:
        return new LogFileDefault();
    }
    return NULL;
}

/**
 * Zwraca obiekt pochodny po LogFormater w zależności od konfiguracji logFormaterFormat.
 */
LogFormater* Factory::newLogFormater()
{
    switch (logFormater)
    {
    case logFormaterNone:
        return NULL;
    case logFormaterEmpty:
        return new LogFormaterEmpty();
    case logFormaterHtml:
        return new LogFormaterHtml();
    }
    return NULL;
}

/**
 * Zwraca nazwę głównego okna w zależności od konfiguracji.
 */
QString Factory::WindowName()
{
    return windowName;
}

/**
 * Zwraca adres do ikony programu w zależności od konfiguracji.
 */
QString Factory::IcoPath()
{
    return icoPath;
}
