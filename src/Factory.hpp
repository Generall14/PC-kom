#ifndef FACTORY_HPP
#define FACTORY_HPP

/**
 * \class Factory
 * @brief Globalna fabryka abstrakcyjna.
 *
 * Fabryka udostępnia statyczne metody zwracające implementacje danej klasy abstrakcyjnej (newFrame(QByteArray) itp.) w zależności od aktualnej konfiguracji. Poza obiektami zwraca
 * również tekst dla okna (WindowName() ), adres ikony (QString IcoPath() ), opis konfiguracji (ConfigDescription() ) oraz wskaźnik wersji udawanej (IsFake() ).
 *
 * Konfiguracja zestawu obiektów jest wczytywana z plików konfiguracyjnych set.cfg (wskazanie zestawu) i configs.xml (zestawy) za pomocą funkcji LoadConfig(), tryb udawany jest
 * ustawiany funkcją setFake(...).
 */

#include <QByteArray>
#include <QFrame>
#include "Frame.hpp"
#include "MediumUI.hpp"
#include "Mendium.hpp"
#include "LogicUI.hpp"
#include "FrameBuilder.hpp"
#include "LogUI.hpp"
#include "LogFile.hpp"
#include "LogFormater.hpp"
#include "BusDevice.hpp"

class Factory
{
    Factory(){}
public:
    static Frame* newFrame(QByteArray ba);
    static MediumUI* newMediumUI(QFrame *fr);
    static Mendium* newMendium();
    static LogicUI* newLogicUI(QFrame *fr);
    static FrameBuilder* newFrameBuilder();
    static LogUI* newLogUI(QFrame* fr);
    static LogFile* newLogFile();
    static LogFormater* newLogFormater();

    static QString WindowName();
    static QString IcoPath();
    static QString ConfigDescription();
    static bool IsFake();

    static void LoadConfig() throw(std::runtime_error);
    static void CreateExampleXML();

    static void setFake(bool fake = true);

private:
    static QString windowName;
    static QString icoPath;
    static QString descConfig;
    static bool fakeVer;

    static QString _frame;
    static QString _mediumUi;
    static QString _mendium;
    static QString _logicUi;
    static QString _frameBuilder;
    static QString _logUi;
    static QString _logFile;
    static QString _logFormater;

    static void terminate(QString arg);
};

#endif
