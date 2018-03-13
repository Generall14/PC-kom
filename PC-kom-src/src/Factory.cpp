#include "Factory.hpp"

#include "Utils/pugixml.hpp"
#include <QFile>
#include <exception>
#include <string>
#include <QMessageBox>

#include "Frame_imp/FrameEmpty.hpp"
#include "Frame_imp/FrameTransparent.hpp"
#include "Frame_imp/FrameSG1.hpp"
#include "Frame_imp/FrameStawrov.hpp"
#include "Frame_imp/FramePazur.hpp"

#include "MediumUI_imp/MediumUIEmpty.hpp"
#include "MediumUI_imp/MediumUIRS.hpp"

#include "Mendium_imp/MendiumEmpty.hpp"
#include "Mendium_imp/MendiumRS.hpp"
#include "Mendium_imp/MendiumFakeSG1.hpp"
#include "Mendium_imp/MendiumFakeStawrow.hpp"
#include "Mendium_imp/MendiumEcho.hpp"

#include "LogicUI_imp/LogicUIEmpty.hpp"
#include "LogicUI_imp/LogicUISG-1.hpp"
#include "LogicUI_imp/LogicUIStawrov.hpp"
#include "LogicUI_imp/LogicUITerminal.hpp"
#include "LogicUI_imp/LogicUIPazur.hpp"

#include "FrameBuilder_imp/FrameBuilderEmpty.hpp"
#include "FrameBuilder_imp/FrameBuilderSG1.hpp"
#include "FrameBuilder_imp/FrameBuilderStawrov.hpp"
#include "FrameBuilder_imp/FrameBuilderTerminal.hpp"
#include "FrameBuilder_imp/FrameBuilderPazur.hpp"

#include "LogUI_imp/LogUIEmpty.hpp"
#include "LogUI_imp/LogUITerm.hpp"

#include "LogFile_imp/LogFileEmpty.hpp"
#include "LogFile_imp/LogFileDefault.hpp"

#include "LogFormater_imp/LogFormaterEmpty.hpp"
#include "LogFormater_imp/LogFormaterHtml.hpp"

QString Factory::windowName = "XXX";
QString Factory::icoPath = "ikona.ico";
QString Factory::descConfig = "brak opisu";
bool Factory::fakeVer = false;
bool Factory::transparent = false;
QString Factory::_frame = "";
QString Factory::_mediumUi = "";
QString Factory::_mendium = "";
QString Factory::_logicUi = "";
QString Factory::_frameBuilder = "";
QString Factory::_logUi = "";
QString Factory::_logFile = "";
QString Factory::_logFormater = "";

/**
 * Zwraca obiekt pochodny po Frame w zależności od konfiguracji frameFormat.
 * @param ba - dane dla obiektu Frame.
 */
Frame* Factory::newFrame(QByteArray ba)
{
    if(transparent)
        return new FrameTransparent(ba);

    if(_frame=="FrameEmpty")
        return new FrameEmpty(ba);
    else if(_frame=="FrameSG1")
        return new FrameSG1(ba);
    else if(_frame=="FrameStawrov")
        return new FrameStawrov(ba);
    else if(_frame=="FrameTransparent")
        return new FrameTransparent(ba);
    else if(_frame=="FramePazur")
        return new FramePazur(ba);
    else
        Factory::terminate("Invalid _frame specifier: \"" + _frame + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po MediumUI w zależności od konfiguracji mediumUiFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
MediumUI* Factory::newMediumUI(QFrame *fr)
{
    if(_mediumUi=="MediumUiRS")
        return new MediumUiRS(fr);
    else if(_mediumUi=="MediumUiEmpty")
        return new MediumUiEmpty(fr);
    else
        Factory::terminate("Invalid _mediumUi specifier: \"" + _mediumUi + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po LogicUI w zależności od konfiguracji logicUiFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
LogicUI* Factory::newLogicUI(QFrame *fr)
{
    if(_logicUi=="LogicUIEmpty")
        return new LogicUIEmpty(fr);
    else if(_logicUi=="LogicUISG1")
        return new LogicUISG1(fr);
    else if(_logicUi=="LogicUIStawrov")
        return new LogicUIStawrov(fr);
    else if(_logicUi=="LogicUITerminal")
        return new LogicUITerminal(fr);
    else if(_logicUi=="LogicUIPazur")
        return new LogicUIPazur(fr);
    else
        Factory::terminate("Invalid _logicUi specifier: \"" + _logicUi + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po Mendium w zależności od konfiguracji mendiumFormat.
 */
Mendium* Factory::newMendium()
{
    if(_mendium=="MendiumEmpty")
        return new MendiumEmpty();
    else if(_mendium=="MendiumRS")
        return new MendiumRS();
    else if(_mendium=="MendiumFakeSG1")
        return new MendiumFakeSG1();
    else if(_mendium=="MendiumFakeStawrow")
        return new MendiumFakeStawrow();
    else if(_mendium=="MendiumEcho")
        return new MendiumEcho();
    else
        Factory::terminate("Invalid _mendium specifier: \"" + _mendium + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po FrameBuilder w zależności od konfiguracji frameBuilderFormat.
 */
FrameBuilder* Factory::newFrameBuilder()
{
    if(_frameBuilder=="FrameBuilderEmpty")
        return new FrameBuilderEmpty();
    else if(_frameBuilder=="FrameBuilderSG1")
        return new FrameBuilderSG1();
    else if(_frameBuilder=="FrameBuilderStawrov")
        return new FrameBuilderStawrov();
    else if(_frameBuilder=="FrameBuilderTerminal")
        return new FrameBuilderTerminal();
    else if(_frameBuilder=="FrameBuilderPazur")
        return new FrameBuilderPazur();
    else
        Factory::terminate("Invalid _frameBuilder specifier: \"" + _frameBuilder + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po LogUI w zależności od konfiguracji logUIFormat.
 * @param fr - wskaźnik do widgetu na którym zbudowany zostanie interfejs.
 */
LogUI* Factory::newLogUI(QFrame* fr)
{
    if(_logUi=="LogUIEmpty")
        return new LogUIEmpty(fr);
    else if(_logUi=="LogUITerm")
        return new LogUITerm(fr);
    else
        Factory::terminate("Invalid _logUi specifier: \"" + _logUi + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po LogFile w zależności od konfiguracji logFileFormat.
 */
LogFile* Factory::newLogFile()
{
    if(_logFile=="LogFileEmpty")
        return new LogFileEmpty();
    else if(_logFile=="LogFileDefault")
        return new LogFileDefault();
    else
        Factory::terminate("Invalid _logFile specifier: \"" + _logFile + "\".");

    return nullptr;
}

/**
 * Zwraca obiekt pochodny po LogFormater w zależności od konfiguracji logFormaterFormat.
 */
LogFormater* Factory::newLogFormater()
{
    if(_logFormater=="LogFormaterEmpty")
        return new LogFormaterEmpty();
    else if(_logFormater=="LogFormaterHtml")
        return new LogFormaterHtml();
    else
        Factory::terminate("Invalid _logFormater specifier: \"" + _logFormater + "\".");

    return nullptr;
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

/**
 * Konfiguruje iplementacje na podstawie plików set.cfg (wskazanie zestawu) i configs.xml (zestawy).
 * @param setName - wskazana nazwa zestawu, jeżeli ciąg jest pusty zestaw zostanie odczytany z pliku set.cfg.
 */
void Factory::LoadConfig(QString setName) throw(std::runtime_error)
{
    if(setName.isEmpty())
    {
        QFile file("set.cfg");
        if(!file.open(QIODevice::ReadOnly))
            throw std::runtime_error("Nie można otworzyć pliku konfiguracyjnego \"" + file.fileName().toStdString() + "\".");

        QTextStream in(&file);
        setName = in.readLine();
        if(setName.isEmpty())
            throw std::runtime_error("Plik konfiguracyjny \"" + file.fileName().toStdString() + "\" nie wskazuje żadnego zestawu implementacji.");

        file.close();
    }

    pugi::xml_document dok;
    pugi::xml_parse_result wynik = dok.load_file("configs.xml");
    if(!wynik)
        throw std::runtime_error("Nie można otworzyć pliku konfiguracyjnego \"configs.xml\".");

    pugi::xml_node mainNode = dok.child("PC-KOM-configs");
    pugi::xml_node chosenNode = mainNode.child(setName.toStdString().c_str());
    if(chosenNode.empty())
        throw std::runtime_error("Brak gałęzi \"" + setName.toStdString() + "\" w pliku konfiguracyjnym.");

    pugi::xml_node implNode = chosenNode.child("Implementations");
    if(implNode.empty())
        throw std::runtime_error("Brak gałęzi \"Implementations\" w zestawie konfiguracyjnym \"" + setName.toStdString() + "\".");
    _frame = implNode.attribute("Frame").as_string();
    _mediumUi = implNode.attribute("MediumUI").as_string();
    _mendium = implNode.attribute("Mendium").as_string();
    _logicUi = implNode.attribute("LogicUI").as_string();
    _frameBuilder = implNode.attribute("FrameBuilder").as_string();
    _logUi = implNode.attribute("LogUI").as_string();
    _logFile = implNode.attribute("LogFile").as_string();
    _logFormater = implNode.attribute("LogFormater").as_string();

    pugi::xml_node descNode = chosenNode.child("Descriptions");
    if(descNode.empty())
        throw std::runtime_error("Brak gałęzi \"Descriptions\" w zestawie konfiguracyjnym \"" + setName.toStdString() + "\".");
    windowName = descNode.attribute("Name").as_string();
    icoPath = descNode.attribute("Ico").as_string();
    descConfig = descNode.attribute("Descrioption").as_string();

    pugi::xml_node fakeNode = chosenNode.child("fake");
    if(fakeNode.empty())
        throw std::runtime_error("Brak gałęzi \"fake\" w zestawie konfiguracyjnym \"" + setName.toStdString() + "\".");
    if(fakeVer)
    {
        QString temp;
        temp = fakeNode.attribute("Frame").as_string();
        if(!temp.isEmpty())
            _frame = temp;
        temp = fakeNode.attribute("MediumUI").as_string();
        if(!temp.isEmpty())
            _mediumUi = temp;
        temp = fakeNode.attribute("Mendium").as_string();
        if(!temp.isEmpty())
            _mendium = temp;
        temp = fakeNode.attribute("LogicUI").as_string();
        if(!temp.isEmpty())
            _logicUi = temp;
        temp = fakeNode.attribute("FrameBuilder").as_string();
        if(!temp.isEmpty())
            _frameBuilder = temp;
        temp = fakeNode.attribute("LogUI").as_string();
        if(!temp.isEmpty())
            _logUi = temp;
        temp = fakeNode.attribute("LogFile").as_string();
        if(!temp.isEmpty())
            _logFile = temp;
        temp = fakeNode.attribute("LogFormater").as_string();
        if(!temp.isEmpty())
            _logFormater = temp;
    }
}

void Factory::CreateExampleXML()
{
    pugi::xml_document xmldoc;
    pugi::xml_node mainNode = xmldoc.append_child("PC-KOM-configs");
    pugi::xml_node exampleNode = mainNode.append_child("empty_set");
    pugi::xml_node imps = exampleNode.append_child("Implementations");
    imps.append_attribute("Frame") = "FrameEmpty";
    imps.append_attribute("FrameBuilder") = "FrameBuilderEmpty";
    imps.append_attribute("LogFile") = "LogFileEmpty";
    imps.append_attribute("LogFormater") = "LogFormaterEmpty";
    imps.append_attribute("LogicUI") = "LogicUIEmpty";
    imps.append_attribute("LogUI") = "LogUIEmpty";
    imps.append_attribute("MediumUI") = "MediumUiEmpty";
    imps.append_attribute("Mendium") = "MendiumEmpty";
    pugi::xml_node descs = exampleNode.append_child("Descriptions");
    descs.append_attribute("Ico") = "ikona.ico";
    descs.append_attribute("Name") = "Chuje muje dzikie węże";
    descs.append_attribute("Descrioption") = "Przykładowa konfiguracja.";
    pugi::xml_node fake = exampleNode.append_child("fake");
    fake.append_attribute("Mendium") = "none";
    xmldoc.save_file("example.xml");
}

/**
 * Ustawia tryb testowy, funkcja aby zadziałała musi być wywołana przed LoadConfig().
 */
void Factory::setFake(bool fake)
{
    fakeVer = fake;
}

/**
 * Funkcja określa czy klasy implementacja Frame ma być generowane według ustalonego schematu (false) lub ma być wymuszona
 * FrameTransparent (true).
 */
void Factory::setTransparent(bool transparentReq)
{
    transparent = transparentReq;
}

bool Factory::getTransparent()
{
    return transparent;
}

void Factory::terminate(QString arg)
{
    QMessageBox::critical(nullptr, "FATAL RUNTIME ERROR!", arg, QMessageBox::Abort);
    exit(-2);
}
