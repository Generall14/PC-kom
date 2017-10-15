#ifndef FACTORY_HPP
#define FACTORY_HPP

/**
 * \class Factory
 * @brief Globalna fabryka abstrakcyjna.
 *
 * Fabryka udostępnia statyczne metody zwracające implementacje danej klasy abstrakcyjnej (newFrame(QByteArray) itp.) w zależności od aktualnej konfiguracji. Poza obiektami zwraca
 * również tekst dla okna (WindowName() ) i adres ikony (QString IcoPath() ).
 *
 * Konfiguracja zestawu obiektów odbywa się poprzez metodę statyczną void Config(...).
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
        mendiumFakeZR3                                                                  /**<Implementacja MendiumFakeZR3*/
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

    static void Config(frameFormat ff, mediumUiFormat muif, mendiumFormat mf, \
                       logicUiFormat lui, frameBuilderFormat fb, logUIFormat lgui, \
                       logFileFormat lff, logFormaterFormat lf, \
                       QString name="Chuje muje dzikie węże", QString ico="ikona.ico");

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

private:
    static frameFormat frame;
    static mediumUiFormat mediumui;
    static mendiumFormat mendium;
    static logicUiFormat logicUi;
    static frameBuilderFormat frameBuilder;
    static logUIFormat logUI;
    static logFileFormat logFile;
    static logFormaterFormat logFormater;

    static QString windowName;
    static QString icoPath;
};

#endif
