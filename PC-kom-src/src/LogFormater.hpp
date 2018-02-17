#ifndef LOGFORMATER_HPP
#define LOGFORMATER_HPP

/**
 * \class LogFormater
 * @brief Interfejs klas formatujących komunikaty.
 *
 * Klasa FrameBuilder wysyła sygnały na sloty FrameWrite(QSharedPointer<Frame>) i FrameReaded(QSharedPointer<Frame>) o przesyłanych pakietach w zależności od kierunku ich przepływu.
 * Klasy LogFormater powinny sformatować odpowiednie teksty a następnie wysłać je do klasy LogUI poprzez sygnał LogUIString(QString, bool) i klasy LogFile przez sygnał
 * LogFileString(QString).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QFrame>
#include <QString>
#include <QObject>
#include "Frame.hpp"
#include "Utils/Desc.hpp"

class LogFormater : public QObject, public Desc
{
    Q_OBJECT
public:
    LogFormater(){Desc::description = "Czysta abstrakcja LogFormater";}
    virtual ~LogFormater(){}

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame) = 0;                           /**<Pakiet został wysłany przez medium transmisyjne*/
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;                          /**<Pakiet został odebrany z medium transmisyjnego*/
    virtual void FrameIgnored(QSharedPointer<Frame> frame) = 0;                         /**<Pakiet został odebrany ale zignorowany na poziomie aplikacji*/

signals:
    void Error(QString msg);                                                            /**<Informowanie o błędzie*/
    void LogFileString(QString str);                                                    /**<Sygnał z komunikatem dla LogFile. @param str - treść komunikatu.*/
    void LogUIString(QString str, bool dirin);                                          /**<Sygnał z komunikatem dla LogUI. @param str - treść komunikatu.
                                                                                        @param dirin - kierunek (1 - z urządzenia do PC)*/
};

#endif
