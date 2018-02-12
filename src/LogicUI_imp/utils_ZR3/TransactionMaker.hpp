#ifndef TRANSACTIONMAKER_HPP
#define TRANSACTIONMAKER_HPP

#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include <QList>
#include <QMutex>
#include "../../Utils/EQThread.hpp"
#include "../../Frame.hpp"
#include "../../Factory.hpp"
#include "transactionDesc.hpp"

class TransactionMaker : public EQThread
{
    Q_OBJECT
public:
    TransactionMaker();
    virtual ~TransactionMaker();

public slots:
    void RecievedData(QByteArray data);

    void RegisterTransaction(TransactionDesc desc);

protected:
    virtual void OnStart();
    virtual void Run();
    virtual void OnStop();

    static const int MAX_MISSES = 3;

    QMutex mutex;
    QList<TransactionDesc> list; // lista aktywnych transakcji
    void SendAsk(TransactionDesc &tr);

signals:
    void Done(uchar _header, QByteArray arr);
    void SendDataFrame(QByteArray);
    void Error(QString);
};

#endif
