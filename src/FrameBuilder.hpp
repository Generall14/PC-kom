#ifndef FRAMEBUILDER_HPP
#define FRAMEBUILDER_HPP

#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QSharedPointer>
#include "Frame.hpp"

class FrameBuilder : public QThread
{
    Q_OBJECT
public:
    FrameBuilder();
    virtual ~FrameBuilder(){}

    void run() final;

public slots:
    void Stop();
    virtual void ByteReaded(QByteArray ba) = 0;
    virtual void FrameWrite(QSharedPointer<Frame> fr) = 0;
    virtual void PureDataWrite(QByteArray ba) = 0;

protected:
    virtual void Run() = 0;

signals:
    void Write(QByteArray);
    void FrameReaded(QSharedPointer<Frame>);
    void Error(QString);

private:
    volatile bool stopRequest = false;
};

#endif
