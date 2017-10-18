#ifndef FRAMEBUSDEVICEUMP_HPP
#define FRAMEBUSDEVICEUMP_HPP

#include <QObject>
#include <QByteArray>
#include <QSharedPointer>
#include "../BusDevice.hpp"
#include "../FrameBuilder_imp/FrameBuilderZR3.hpp"

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

    uchar myADr;
    uchar nextAdr;
    FrameBuilderZR3* frameBuilder = NULL;

    void ParseConfigFile(QByteArray data);

    QMutex mutex;
    QByteArray gtemp;
//    QByteArray gotemp;

signals:
    void toFrameByteReaded(QByteArray);
    void Halt();

};

#endif
