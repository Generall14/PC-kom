#ifndef EQTHREAD_HPP
#define EQTHREAD_HPP

#include <QObject>
#include <QThread>

class EQThread : public QThread
{
    Q_OBJECT
public:
    EQThread(QObject* parent = NULL);
    virtual ~EQThread(){}

    void run() final;

public slots:
    virtual void Stop();

protected:
    virtual void Run() = 0;
    virtual void OnStop();
    volatile bool stopRequest = false;
};

#endif
