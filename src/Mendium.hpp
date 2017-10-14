#ifndef MENDIUM_HPP
#define MENDIUM_HPP

/**
 * \class Mendium
 * @brief Interfejs klas obsługujących medium transmisyjne.
 *
 * Klasa działa w osobnym wątku (na zasadach dziedziczonych po EQThread).
 *
 * Implementuje zwracanie logicznego stanu opened w metodzie isOpened() oraz metodę Stop() dziedziczoną po EQThread. Pozostałe metody są czysto wirtualne.
 *
 * Sterowanie stanem medium zapewniają sloty Open(QString) oraz Close(), pobudzanę są sygnałami z klas MediumUI. Zmiana stanu powinna być zaznaczona rozesłaniem sygnału Opened()
 * bądź Closed().
 *
 * Slot Write(QSharedPointer<Frame>) obsługuje zapis danych do medium transmisyjnego, sygnały na ten slot pochodzą z klasy FrameBuilder (gdzie zostały wymuszone przez LogicUI).
 * Wszystkie odczytane dane z medium powinny być rozesłane przez sygnał Readed(QByteArray) (trafią do FrameBuilder).
 *
 * Metoda Flush() powinna opróżniać wszelkie bufory zapisu i odczytu (jeżeli takowe istnieją).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QObject>
#include "EQThread.hpp"
#include <QByteArray>
#include "Frame.hpp"
#include <QSharedPointer>

class Mendium : public EQThread
{
    Q_OBJECT
public:
    Mendium();
    virtual ~Mendium(){}

public slots:
    bool isOpened();                                                                    /**<Czy medium jest otwarte*/
    virtual void Stop();                                                                /**<Zatrzymaj wątek*/
    virtual void Open(QString desc) = 0;                                                /**<Otwórz medium opisane tekstem desc*/
    virtual void Close() = 0;                                                           /**<Zamknij medium*/
    virtual void Write(QSharedPointer<Frame> frame) = 0;                                /**<Wyslij ramkę do medium*/
    virtual void Flush() = 0;                                                           /**<Opróżnij bufory*/

protected:
    virtual void Run() = 0;
    bool opened = false;

signals:
    void Opened();                                                                      /**<Otwarto medium*/
    void Closed();                                                                      /**<Zamknięto medium*/
    void Readed(QByteArray);                                                            /**<Odczytano dane z medium*/
    void Error(QString);                                                                /**<Komunikacja błędu*/
};

#endif
