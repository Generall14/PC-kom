#include "Factory.hpp"

#include "Frame_imp/FrameEmpty.hpp"
#include "Frame_imp/FrameTransparent.hpp"
#include "Frame_imp/FrameSG1.hpp"
#include "Frame_imp/FrameStawrov.hpp"
#include "Frame_imp/FrameZR3.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"
#include "Mendium_imp/MendiumFakeSG1.hpp"
#include "Mendium_imp/MendiumFakeStawrow.hpp"
#include "Mendium_imp/MendiumBusConnector.hpp"

#include "LogicUI_imp/LogicUIEmpty.hpp"
#include "LogicUI_imp/LogicUISG-1.hpp"
#include "LogicUI_imp/LogicUIStawrov.hpp"
#include "LogicUI_imp/LogicUIZR3.hpp"

#include "FrameBuilder_imp/FrameBuilderEmpty.hpp"
#include "FrameBuilder_imp/FrameBuilderSG1.hpp"
#include "FrameBuilder_imp/FrameBuilderStawrov.hpp"
#include "FrameBuilder_imp/FrameBuilderZR3.hpp"

#include "LogUI_imp/LogUIEmpty.hpp"
#include "LogUI_imp/LogUITerm.hpp"

#include "LogFile_imp/LogFileEmpty.hpp"
#include "LogFile_imp/LogFileDefault.hpp"

#include "LogFormater_imp/LogFormaterEmpty.hpp"
#include "LogFormater_imp/LogFormaterHtml.hpp"

#include "BusDevice_imp/BusDeviceUMP.hpp"
#include "BusDevice_imp/BusDeviceUMPZR3.hpp"

Factory::frameFormat Factory::frame = Factory::frameEmpty;
Factory::mediumUiFormat Factory::mediumui = Factory::mediumUIEmpty;
Factory::mendiumFormat Factory::mendium = Factory::mendiumEmpty;
Factory::logicUiFormat Factory::logicUi = Factory::logicUiEmpty;
Factory::frameBuilderFormat Factory::frameBuilder = Factory::frameBuilderEmpty;
Factory::logUIFormat Factory::logUI = Factory::logUIEmpty;
Factory::logFileFormat Factory::logFile = Factory::logFileEmpty;
Factory::logFormaterFormat Factory::logFormater = Factory::logFormaterEmpty;
Factory::busDeviceFormat Factory::busDFormat = Factory::busDeviceNone;
QString Factory::windowName = "XXX";
QString Factory::icoPath = "ikona.ico";
QString Factory::descConfig = "brak opisu";
bool Factory::fakeVer = false;

/**
 * Funkcja służy do określenia które konkretne implementacje będą zwracane w metodach fabryki abstrakcyjnej. Dodatkowo wskazuje nazwę dla głównego okna programu
 * i adres do ikony.
 */
void Factory::ConfigIml(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, logicUiFormat lui, frameBuilderFormat fb, logUIFormat lgui, \
                     logFileFormat lff, logFormaterFormat lf)
{
    Factory::frame = ff;
    Factory::mediumui = muif;
    Factory::mendium = mf;
    Factory::logicUi = lui;
    Factory::frameBuilder = fb;
    Factory::logUI = lgui;
    Factory::logFile = lff;
    Factory::logFormater = lf;
}

/**
 * Funkcja ustawia adres ikony, nazwę głównego okna oraz opis konfiguracji.
 */
void Factory::ConfigDesc(QString desc, QString name, QString ico)
{
    Factory::descConfig = desc;
    Factory::windowName = name;
    Factory::icoPath = ico;
}

/**
 * Funkcja określa implementację klasy Mendium i ustawia znacznik udawanej konfiguracji.
 */
void Factory::MakeFake(mendiumFormat mf, busDeviceFormat bdf)
{
    Factory::mendium = mf;
    Factory::fakeVer = true;
    busDFormat = bdf;
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
    case Factory::frameZR3:
        return new FrameZR3(ba);
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
    case Factory::logicUIZR3:
        return new LogicUIZR3(fr);
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
    case Factory::mandiumBusConnector:
        return new MendiumBusConnector();
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
        return new FrameBuilderEmpty();
    case frameBuilderSG1:
        return new FrameBuilderSG1();
    case frameBuilderStawrov:
        return new FrameBuilderStawrov();
    case frameBuilderZR3:
        return new FrameBuilderZR3();
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
 * Zwraca obiekt pochodny po BusDevice w zależności od konfiguracji busDeviceFormat.
 */
BusDevice* Factory::newBusDevice(QString arg)
{
    switch (busDFormat)
    {
    case busDeviceNone:
        return NULL;
    case busDeviceUMP:
        return new BusDeviceUMP(arg);
    case busDeviceUMPZR3:
        return new BusDeviceUMPZR3(arg);
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

/**
 * Zwraca opis konfiguracji.
 */
QString Factory::ConfigDescription()
{
    return descConfig;
}

/**
 * Zwraca znacznik udawanej konfiguracji.
 */
bool Factory::IsFake()
{
    return fakeVer;
}
