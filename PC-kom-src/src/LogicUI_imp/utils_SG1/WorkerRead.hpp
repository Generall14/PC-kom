#ifndef WORKERREAD_HPP
#define WORKERREAD_HPP

#include <QObject>
#include "Worker.hpp"

class WorkerRead : public Worker
{
    Q_OBJECT
public:
    WorkerRead(uchar offset, int timeout, int repeates);
    virtual ~WorkerRead();

    virtual bool isItOk(QByteArray frame);

private:
    uchar _offset;
};

#endif
