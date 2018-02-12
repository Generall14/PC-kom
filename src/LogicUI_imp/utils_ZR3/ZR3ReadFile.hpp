#ifndef ZR3READFILE_HPP
#define ZR3READFILE_HPP

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include "../../Utils/EQThread.hpp"
#include "../../Frame.hpp"
#include "../../Factory.hpp"

class ZR3ReadFile : public EQThread
{
    Q_OBJECT
public:
    ZR3ReadFile(uchar header);
    virtual ~ZR3ReadFile();

public slots:
    void RecievedData(QByteArray data);

protected:
    virtual void OnStart();
    virtual void Run();
    virtual void OnStop();

    static const int MAX_MISSES = 3;

    uint16_t curroffset = 0;
    int miss = MAX_MISSES;
    QByteArray temp;
    QTimer* timer = NULL;

    uchar _header;

    void Send();

protected slots:
    void timeouted();

signals:
    void Done(uchar _header, QByteArray arr);
    void SendDataFrame(QByteArray);
    void Error(QString);
    void StopTimer();
};

#endif
