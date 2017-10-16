#ifndef FRAMEBUILDER_HPP
#define FRAMEBUILDER_HPP

/**
 * \class FrameBuilder
 * @brief Interfejs warstwy protokołu.
 *
 * Klasa otrzymuje (na slot ByteReaded(QByteArray) ) od obiektu Mendium dane odebrane z medium transmisyjnego w postaci niesformatowanego ciągu bajtów. Na klasie FrameBuilder leży
 * odpowiedzialność za kontrolowanie protokołu przesyłu danych, tj. sprawdzanie poprawności otrzymanych danych, nadzór nad timingami oraz zamienianie ciągu otrzymanych danych na
 * obiekty Frame. Krótko mówiąc, klasa jest odpowiedzialna za realizację warstwy protokołu danych.
 *
 * Dane zamienione na ramki Frame (również te niepoprawne) wysyłane są sygnałem FrameReaded(QSharedPointer<Frame>) do klasy reprezentującej logikę i warstwę aplikacji - LogicUI.
 *
 * FrameBuilder na sloty FrameWrite(QSharedPointer<Frame>) i PureDataWrite(QByteArray) otrzymuje żądania wysłania danych (od LogicUI) które przekazuje sygnałem Write(QSharedPointer<Frame>)
 * do obiektu Mandium.
 *
 * Sygnały Write(QSharedPointer<Frame>) i FrameReaded(QSharedPointer<Frame>) odbierane są też przez LogFormater.
 *
 * Klasa działa w osobnym wątku (na zasadach dziedziczonych po EQThread).
 *
 * Sygnalizacja wszelkich błędów odbywa się za pomocą sygnału Error(QString).
 */

#include <QObject>
#include "Utils/EQThread.hpp"
#include <QByteArray>
#include <QSharedPointer>
#include "Frame.hpp"
#include "Utils/Desc.hpp"

class FrameBuilder : public EQThread, public Desc
{
    Q_OBJECT
public:
    FrameBuilder(){Desc::description = "Czysta abstrakcja FrameBuilder";}
    virtual ~FrameBuilder(){}

public slots:
    virtual void ByteReaded(QByteArray ba) = 0;                                         /**<Dane odebrane z medium transmisyjnego*/
    virtual void FrameWrite(QSharedPointer<Frame> fr) = 0;                              /**<Żądanie wysłania pakietu*/
    virtual void PureDataWrite(QByteArray ba) = 0;                                      /**<Żądanie wysłania danych*/

signals:
    void Write(QSharedPointer<Frame>);                                                  /**<Sygnał z żadaniem wysłania pakietu*/
    void FrameReaded(QSharedPointer<Frame>);                                            /**<Sygnał z odebranym pakietem*/
    void Error(QString);                                                                /**<Informowanie o błędzie*/
};

#endif
