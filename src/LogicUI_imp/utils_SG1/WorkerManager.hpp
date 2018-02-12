#ifndef WORKERMANAGER_HPP
#define WORKERMANAGER_HPP

#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include "../../Utils/EQThread.hpp"
#include "../../Frame.hpp"
#include "Worker.hpp"

class WorkerManager : public EQThread
{
    Q_OBJECT
public:
    WorkerManager(QVector<Worker*> vec, int maxActiveThreads);
    virtual ~WorkerManager();

public slots:
    void RecievedFrame(QByteArray frame);

protected:
    virtual void Run();
    QVector<Worker*> transVec;
    int maxThreads;
    int activeThreads = 0;
    int started = 0;
    int failed = 0;
    int done = 0;

protected slots:
    void ThreadDone();
    void ThreadFail();

signals:
    void Done();
    void SendFrame(QByteArray);
    void Fail(QString);
    void Error(QString);
    void InternaFrameCast(QByteArray);
};

#endif
