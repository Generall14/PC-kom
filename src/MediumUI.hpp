#ifndef MEDIUMUI_HPP
#define MEDIUMUI_HPP

/**
 * \class MediumUI
 * @brief Interfejs użytkownika do wyboru medium transmisyjnego.
 *
 * Pobiera w konstruktorze a nastepnie przetrzymuje w zmiennej cParent wskaźnik na obiekt QFrame na którym będzie budowany interjejs graficzny. Inicjalizacja interfejsu
 * powinna nastapić w metodzie wirtualnej Init().
 *
 * Na sloty Connected() oraz Disconnected() przesyłane są sygnały od klasy Mendium informujące o stanie połączenia. Interfejs powinien odpowiednio na nie zareagować poprzez
 * wygaszenie odpowiednich opcji.
 *
 * Klasa zależnie od poczynań użytkownika powinna wysyłać sygnały DisconnectRequest() oraz ConnectRequest(QString) w celu zarządzania połączeniem w klasie Mendium. Argument w sygnale
 * ConnectRequest(QString) powinien opisywać parametry połączenia zgodnie z wymaganiami danej implementacji interfejsu Mendium.
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QFrame>
#include <QString>
#include <QObject>

class MediumUI : public QObject
{
    Q_OBJECT
public:
    MediumUI(QFrame* parent);
    virtual ~MediumUI(){}

    virtual void Init() = 0;                                                            /**<Inicjalizacja interfejsu użytkownika*/

public slots:
    virtual void Connected() = 0;                                                       /**<Reakcja na połączenie z medium*/
    virtual void Disconnected() = 0;                                                    /**<Reakcja na rozłączenie z medium*/

signals:
    void ConnectRequest(QString desc);                                                  /**<Żądanie połączenia z medium*/
    void DisconnectRequest();                                                           /**<Żądanie rozłączenia z medium*/
    void Error(QString msg);                                                            /**<Informowanie o błędzie*/

protected:
    QFrame* cParent=NULL;                                                               /**<Wskaźnik na podstawę interfejsu użytkownika*/
};

#endif
