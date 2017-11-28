#ifndef FRAMEBUSDEVICEUMPZR3_HPP
#define FRAMEBUSDEVICEUMPZR3_HPP

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QMutex>
#include "BusDeviceUMP.hpp"

class BusDeviceUMPZR3 : public BusDeviceUMP
{
    Q_OBJECT
public:
    BusDeviceUMPZR3(QString arg);
    virtual ~BusDeviceUMPZR3(){}

protected:
    struct ars
    {
        float timer, expireTimer;
        int startTime;
        uchar header;
        QByteArray (BusDeviceUMPZR3::*fptr)();
    };

    QMutex mutex;
    QList<ars> alist;

    float time = 0;
    float currentDoseRate;
    long long currentDose = 0;
    long long doseAlarm = 1000;
    bool doseAlarmState = false;

    virtual void OnRun();
    virtual QByteArray OnDataRecieved(QByteArray data);

    static const int TIME_TO_EXPIRE_S = 30;

    QByteArray DoseData();
    QByteArray SetDoseData(QByteArray dat);
    QByteArray DoseAlarmStateData();
    QByteArray SetDoseAlarmLevelData(QByteArray dat);
    QByteArray GetDoseAlarmLevelData();
    QByteArray DoseRateData();
    QByteArray StatusData();
    QByteArray EstData();
    QByteArray AutoReportData(QByteArray dat);
};

#endif
