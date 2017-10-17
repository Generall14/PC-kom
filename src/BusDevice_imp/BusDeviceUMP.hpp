#ifndef FRAMEBUSDEVICEUMP_HPP
#define FRAMEBUSDEVICEUMP_HPP

#include <QObject>
#include <QByteArray>
#include <QSharedPointer>
#include "../BusDevice.hpp"

class BusDeviceUMP : public BusDevice
{
    Q_OBJECT
public:
    BusDeviceUMP(QString arg);
    virtual ~BusDeviceUMP(){}

public slots:
    virtual void ByteReaded(QByteArray ba);

protected:
    virtual void OnStart();
    virtual void OnStop();
    virtual void Run();
};

#endif
