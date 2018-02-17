#ifndef LOGUI_HPP
#define LOGUI_HPP

/**
 * \class LogUI
 * @brief Interfejs klas odpowiedzialnych za wyświetlanie logów w GUI.
 *
 * Pobiera w konstruktorze a nastepnie przetrzymuje w zmiennej cParent wskaźnik na obiekt QFrame na którym będzie budowany interjejs graficzny. Inicjalizacja interfejsu
 * powinna nastapić w metodzie wirtualnej Init().
 *
 * Na slot LogString(QString, bool) dostarczany jest tekst logu oraz kierunek z którym jest związany, slot ten jest wywoływany przez klasę LogFormater.
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QFrame>
#include <QString>
#include <QObject>
#include "Utils/Desc.hpp"

class LogUI : public QObject, public Desc
{
    Q_OBJECT
public:
    LogUI(QFrame* parent);                                                              /**<Konstruktor. @param parent - wskaźnik na widget na którym będzie zbudowany interfejs*/
    virtual ~LogUI(){}

    virtual void Init() = 0;                                                            /**<Inicjalizacja interfejsu użytkownika*/

public slots:
    virtual void LogString(QString str, bool dirin) = 0;                                /**<Żądanie wyświetlania komunikatu. @param str - treść komunikatu.
                                                                                        @param dirin - kierunek (1 - z urządzenia do PC)*/
signals:
    void Error(QString msg);                                                            /**<Informowanie o błędzie*/

protected:
    QFrame* cParent=NULL;                                                               /**<Wskaźnik na podstawę interfejsu użytkownika*/
};

#endif
