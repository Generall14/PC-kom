#ifndef LPOGICUI_HPP
#define LPOGICUI_HPP

/**
 * \class LogicUI
 * @brief Interfejs klas odpowiedzialnych za GUI oraz logikę programu.
 *
 * Logikę programu w sensie - co z tą transmisją zrobić dalej zrobić, jak i do czego ją wykorzystać.
 *
 * Pobiera w konstruktorze a nastepnie przetrzymuje w zmiennej cParent wskaźnik na obiekt QFrame na którym będzie budowany interjejs graficzny. Inicjalizacja interfejsu
 * powinna nastapić w metodzie wirtualnej Init().
 *
 * Na slot FrameReaded(QSharedPointer<Frame>) przesyłane (od FrameBuilder) będą pakiety danych odczytane z medium transmisyjnego. Żądania wysłania danych (trafiają do FrameBuilder)
 * realizowane są przez sygnały WriteFrame(QSharedPointer<Frame>) oraz WritePureData(QByteArray).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame.hpp"
#include "Utils/Desc.hpp"

class LogicUI : public QObject, public Desc
{
    Q_OBJECT
public:
    LogicUI(QFrame* parent);                                                            /**<Konstruktor. @param parent - wskaźnik na widget na którym będzie zbudowany interfejs*/
    virtual ~LogicUI(){}

    virtual void Init() = 0;                                                            /**<Inicjalizacja interfejsu użytkownika*/

public slots:
    virtual void Connected() = 0;                                                       /**<Reakcja na połączenie z medium*/
    virtual void Disconnected() = 0;                                                    /**<Reakcja na rozłączenie z medium*/
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;                          /**<Odebrany pakiet danych*/

signals:
    void Error(QString msg);                                                            /**<Informowanie o błędzie*/
    void WriteFrame(QSharedPointer<Frame> frame);                                       /**<Żądanie wysłania pakietu danych*/
    void WritePureData(QByteArray data);                                                /**<Żądanie wysłania czystych danych*/

protected:
    QFrame* cParent=nullptr;                                                               /**<Wskaźnik na podstawę interfejsu użytkownika*/
};

#endif
