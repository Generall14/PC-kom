#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>
#include <QSharedPointer>
#include "../../Utils/EQThread.hpp"
#include "../../Frame.hpp"

class Worker : public EQThread
{
    Q_OBJECT
public:
    Worker(QByteArray dataToSend, int timeout, int repeates);
    virtual ~Worker();

    virtual bool isItOk(QByteArray frame) = 0;

    void setDataToSend(QByteArray newData);

public slots:
    void RecievedFrame(QByteArray frame);

private:
    virtual void Run();
    QByteArray _dataToSend;
    int _timeout;
    int _repeates;
    int counter = 0;
    bool done = false;

signals:
    void Done(QByteArray);
    void SendFrame(QByteArray);
    void Fail();
    void Error(QString);
};

#endif
