#ifndef WORKER_HPP
#define WORKER_HPP

#include <QObject>
#include <QSharedPointer>
#include "../../EQThread.hpp"
#include "Transaction.hpp"
#include "../../Frame.hpp"

class Worker : public EQThread
{
    Q_OBJECT
public:
    Worker(transaction req);
    virtual ~Worker();

public slots:
    void RecievedFrame(QByteArray frame);

protected:
    virtual void Run();
    transaction transactionRequest;
    int counter = 0;
    bool done = false;

signals:
    void Done(QByteArray);
    void SendFrame(QByteArray);
    void Fail();
    void Error(QString);
};

#endif
