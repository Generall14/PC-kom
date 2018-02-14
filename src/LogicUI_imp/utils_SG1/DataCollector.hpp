#ifndef DATACOLLECTOR_HPP
#define DATACOLLECTOR_HPP

#include <QObject>
#include <QSharedPointer>
#include <QList>
#include "../../Utils/EQThread.hpp"
#include "../../Frame.hpp"
#include "../../Factory.hpp"

class DataCollector : public EQThread
{
    Q_OBJECT
public:
    enum method
    {
        metImp,
        metRap
    };

    DataCollector(int numberOfData, method typPomiaru = metRap, bool continuous = true);
    virtual ~DataCollector();

public slots:
    void RecievedFrame(QByteArray frame);

protected:
    virtual void Run();
    virtual void OnStop();

    void CalcData();

    QList<int> dataList;
    QList<int> ADCList;
    int length;
    method typ;
    bool ciagly;
    float timeres;

protected slots:

signals:
    void Done();
    void SendFrame(QByteArray);
    void SendStatus(float, int, int); //średnia zliczeń, średnia ADC, postęp (x/1000)
    void Error(QString);
};

#endif
