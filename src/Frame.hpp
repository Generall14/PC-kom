#ifndef FRAME_HPP
#define FRAME_HPP

/**
 * \class Frame
 * @brief Interfejs klas przechowujących pakiety.
 *
 * Klasa przechowuje dane pakietów oraz tłumaczy je na opis tekstowy (metody QString toQString(), QString toShortQString()) i wartość przenoszoną jeżeli taka istnieje (magicNumbers() ).
 * Sprawdza również w metodzie isValid() czy pakiet jest poprawny.
 *
 * Jedynym slotem klasy jest LogString(QString) na który są przesyłane sygnały od LogFormater z przygotowanym tekstem do zapisu. Zadaniem klasy jest zapis komunikatów do plików
 * (lub w razie potrzeby do czegokolwiek zasadnego).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QString>
#include <QByteArray>
#include <QSharedPointer>
#include <QMutex>
#include "Utils/Desc.hpp"

class Frame : public Desc
{
    Frame(){}
public:
    Frame(QByteArray data);
    virtual ~Frame();

    virtual bool isValid() = 0;                 /**<Informuje czy ramka jest prawodłowa.*/
    virtual QString toQString() = 0;            /**<Tworzy string opisujący zawartość, np. "Pomiar czasu".*/
    virtual QString toShortQString() = 0;       /**<Tworzy zwięzły string z samą wartością przenoszoną w ramce, np. "100 ms".*/
    virtual QByteArray magicNumbers() = 0;      /**<Zwraca wartość jednoznacznie identyfikującą typ zawartości, np nagłówek.*/

    QByteArray pureData();                      /**<Zwraca czałość jako QByteArray.*/

protected:
    QByteArray pck;                             /**<Dane.*/
};

#endif
