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

    virtual void OnRun();
    virtual QByteArray OnDataRecieved(QByteArray data);

    uchar myADr;
    uchar nextAdr;
    QByteArray stringTable;
    QByteArray deviceDescriptor;
    QByteArray methodsDescriptor;
    FrameBuilderZR3* frameBuilder = NULL;

    void ParseConfigFile(QByteArray data);
    QByteArray GetFileData(QByteArray& ba, uint16_t ptr, uint8_t size);

    static const uint8_t MAX_DATA_FILE_SIZE = 63;
    static const uint TIME_STEP_MS = 20;

protected slots:
    void AplFrameReaded(QSharedPointer<Frame> fr);

signals:
    void toFrameByteReaded(QByteArray);
    void Halt();
    void AplWritePureData(QByteArray arr);
};

#endif
