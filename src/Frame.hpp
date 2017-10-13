#ifndef FRAME_HPP
#define FRAME_HPP
/**
* @class Frame
*
* Interfejs klas przechwujących pakiety.
*/

#include <QString>
#include <QByteArray>

class Frame
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
