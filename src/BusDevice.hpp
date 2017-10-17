#ifndef FRAMEBUSDEVICE_HPP
#define FRAMEBUSDEVICE_HPP

/**
 * \class BusDevice
 * @brief Klasa udająca urządzenie na udawanej magistrali MediumBusConnector.
 *
 * Implementacje BusDevice są łączone przez MediumBusConnector w udawaną magistralę (dane są rozsyłąne pomiędzy wszystkimi obiektami, łącznie z logiką programu).
 */

#include <QObject>
#include "Utils/EQThread.hpp"
#include <QByteArray>
#include <QSharedPointer>
#include "Utils/Desc.hpp"

class BusDevice : public EQThread, public Desc
{
    Q_OBJECT
public:
    BusDevice(QString arg):_arg(arg){Desc::description = "Czysta abstrakcja BusDevice";}
    virtual ~BusDevice(){}

public slots:
    virtual void ByteReaded(QByteArray ba) = 0;                                         /**<Dane odebrane z magistrali*/

signals:
    void Write(QByteArray);                                                             /**<Sygnał z danymi wysyłanymi na magistrale*/
    void Error(QString);                                                                /**<Informowanie o błędzie*/

protected:
    QString _arg;
};

#endif
