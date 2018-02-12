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
    enum frameFormat                                                                    /**Określa implementację klasy Frame*/
    {
        frameNone,                                                                      /**<Wskaźnik NULL*/
        frameEmpty,                                                                     /**<Implementacja FrameEmpty*/
        frameTransparent,                                                               /**<Implementacja FrameTransparent*/
        frameSG1,                                                                       /**<Implementacja FrameSG1*/
        frameStawrov,                                                                   /**<Implementacja FrameStawrov*/
        frameZR3                                                                        /**<Implementacja FrameZR3*/
    };

    enum mediumUiFormat                                                                 /**Określa implementację klasy MediumUI*/
    {
        mediumUINone,                                                                   /**<Wskaźnik NULL*/
        mediumUIEmpty,                                                                  /**<Implementacja MediumUiEmpty*/
        mediumUIRS                                                                      /**<Implementacja MediumUiRS*/
    };

    enum mendiumFormat                                                                  /**Określa implementację klasy Mendium*/
    {
        mendiumNone,                                                                    /**<Wskaźnik NULL*/
        mendiumEmpty,                                                                   /**<Implementacja MendiumEmpty*/
        mendiumRS,                                                                      /**<Implementacja MendiumRS*/
        mendiumFakeGS1,                                                                 /**<Implementacja MendiumFakeSG1*/
        mendiumFakeStawrow,                                                             /**<Implementacja MendiumFakeStawrow*/
        mandiumBusConnector                                                             /**<Implementacja MendiumBusConnector*/
    };

    enum logicUiFormat                                                                  /**Określa implementację klasy LogicUI*/
    {
        logicUiNone,                                                                    /**<Wskaźnik NULL*/
        logicUiEmpty,                                                                   /**<Implementacja LogicUIEmpty*/
        logicUiSG1,                                                                     /**<Implementacja LogicUISG1*/
        logicUIStawrov,                                                                 /**<Implementacja LogicUIStawrov*/
        logicUIZR3                                                                      /**<Implementacja LogicUIZR3*/
    };

    enum frameBuilderFormat                                                             /**Określa implementację klasy FrameBuilder*/
    {
        frameBuilderNone,                                                               /**<Wskaźnik NULL*/
        frameBuilderEmpty,                                                              /**<Implementacja FrameBuilderEmpty*/
        frameBuilderSG1,                                                                /**<Implementacja FrameBuilderSG1*/
        frameBuilderStawrov,                                                            /**<Implementacja FrameBuilderStawrov*/
        frameBuilderZR3                                                                 /**<Implementacja FrameBuilderZR3*/
    };

    enum logUIFormat                                                                    /**Określa implementację klasy LogUI*/
    {
        logUINone,                                                                      /**<Wskaźnik NULL*/
        logUIEmpty,                                                                     /**<Implementacja LogUIEmpty*/
        logUITerm                                                                       /**<Implementacja LogUITerm*/
    };

    enum logFileFormat                                                                  /**Określa implementację klasy LogFile*/
    {
        logFileNone,                                                                    /**<Wskaźnik NULL*/
        logFileEmpty,                                                                   /**<Implementacja LogFileEmpty*/
        logFileDefault                                                                  /**<Implementacja LogFileDefault*/
    };

    enum logFormaterFormat                                                              /**Określa implementację klasy LogFormater*/
    {
        logFormaterNone,                                                                /**<Wskaźnik NULL*/
        logFormaterEmpty,                                                               /**<Implementacja LogFormaterEmpty*/
        logFormaterHtml                                                                 /**<Implementacja LogFormaterHtml*/
    };

    enum busDeviceFormat                                                                /**Określa implementację klasy BusDevice*/
    {
        busDeviceNone,                                                                  /**<Wskaźnik NULL*/
        busDeviceUMP,                                                                   /**<Implementacja BusDeviceUMP*/
        busDeviceUMPZR3                                                                 /**<Implementacja BusDeviceUMPZR3*/
    };

    static void ConfigIml(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, \
                       logicUiFormat lui, frameBuilderFormat fb, logUIFormat lgui, \
                       logFileFormat lff, logFormaterFormat lf);
    static void ConfigDesc(QString desc, QString name="Chuje muje dzikie węże", QString ico="ikona.ico");
    static void MakeFake(mendiumFormat mf, busDeviceFormat bdf = busDeviceNone);

    static Frame* newFrame(QByteArray ba);
    static MediumUI* newMediumUI(QFrame *fr);
    static Mendium* newMendium();
    static LogicUI* newLogicUI(QFrame *fr);
    static FrameBuilder* newFrameBuilder();
    static LogUI* newLogUI(QFrame* fr);
    static LogFile* newLogFile();
    static LogFormater* newLogFormater();
    static BusDevice* newBusDevice(QString arg);//-----------------------------------------------------

    static QString WindowName();
    static QString IcoPath();
    static QString ConfigDescription();
    static bool IsFake();

    static void LoadConfig() throw(std::runtime_error);
    static void CreateExampleXML();

    static void setFake(bool fake = true);

private:
    static frameFormat frame;
    static mediumUiFormat mediumui;
    static mendiumFormat mendium;
    static logicUiFormat logicUi;
    static frameBuilderFormat frameBuilder;
    static logUIFormat logUI;
    static logFileFormat logFile;
    static logFormaterFormat logFormater;
    static busDeviceFormat busDFormat;

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
