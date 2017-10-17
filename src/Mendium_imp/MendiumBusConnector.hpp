#ifndef MENDIUMBUSCONNECTOR_HPP
#define MENDIUMBUSCONNECTOR_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumBusConnector : public Mendium
{
    Q_OBJECT
public:
    MendiumBusConnector();
    virtual ~MendiumBusConnector(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame>);
    virtual void Flush();

protected:
    virtual void Run();
};

#endif
