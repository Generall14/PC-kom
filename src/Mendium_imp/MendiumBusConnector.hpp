#ifndef MENDIUMBUSCONNECTOR_HPP
#define MENDIUMBUSCONNECTOR_HPP

#include "../Mendium.hpp"
#include "../BusDevice.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>
#include <QVector>

class MendiumBusConnector : public Mendium
{
    Q_OBJECT
public:
    MendiumBusConnector();
    virtual ~MendiumBusConnector(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame> fr);
    virtual void Flush();

    void ByteWrite(QByteArray ar);

protected:
    virtual void Run();
    virtual void OnStart();
    virtual void OnStop();

    QVector<BusDevice*> devicesVector;

    QMutex mutex;
    QByteArray gtemp;

signals:
    void HALT();
};

#endif
