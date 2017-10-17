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
    BusDeviceUMP(QByteArray arg);
    virtual ~BusDeviceUMP(){}

public slots:
    virtual void ByteReaded(QByteArray ba);

protected:
    virtual void Run();
};

#endif
