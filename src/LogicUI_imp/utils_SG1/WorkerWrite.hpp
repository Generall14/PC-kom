#ifndef WORKERWRITE_HPP
#define WORKERWRITE_HPP

#include <QObject>
#include "Worker.hpp"

class WorkerWrite : public Worker
{
    Q_OBJECT
public:
    WorkerWrite(uchar offset, QByteArray data, int timeout, int repeates);
    virtual ~WorkerWrite();

    virtual bool isItOk(QByteArray frame);

private:
    uchar _offset;
    QByteArray _data;
};

#endif
