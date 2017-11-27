#ifndef FRAMEBUSDEVICEUMPZR3_HPP
#define FRAMEBUSDEVICEUMPZR3_HPP

#include <QObject>
#include <QByteArray>
#include "BusDeviceUMP.hpp"

class BusDeviceUMPZR3 : public BusDeviceUMP
{
    Q_OBJECT
public:
    BusDeviceUMPZR3(QString arg);
    virtual ~BusDeviceUMPZR3(){}

protected:
    virtual void OnRun();
    virtual QByteArray OnDataRecieved(QByteArray data);
};

#endif
