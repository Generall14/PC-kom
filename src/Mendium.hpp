#ifndef MENDIUM_HPP
#define MENDIUM_HPP

#include <QObject>
#include "EQThread.hpp"
#include <QByteArray>
#include "Frame.hpp"
#include <QSharedPointer>

class Mendium : public EQThread
{
    Q_OBJECT
public:
    Mendium();
    virtual ~Mendium(){}

public slots:
    bool isOpened();
    virtual void Stop();
    virtual void Open(QString desc) = 0;
    virtual void Close() = 0;
    virtual void Write(QSharedPointer<Frame> frame) = 0;
    virtual void Flush() = 0;

protected:
    virtual void Run() = 0;
    bool opened = false;

signals:
    void Opened();
    void Closed();
    void Readed(QByteArray);
    void Error(QString);
};

#endif
