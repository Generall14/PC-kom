#ifndef MENDIUM_HPP
#define MENDIUM_HPP

#include <QObject>
#include <QThread>
#include <QByteArray>
#include "Frame.hpp"
#include <QSharedPointer>

class Mendium : public QThread
{
    Q_OBJECT
public:
    Mendium();
    virtual ~Mendium(){}

    void run() final;

public slots:
    void Stop();
    bool isOpened();
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

private:
    volatile bool stopRequest = false;
};

#endif
