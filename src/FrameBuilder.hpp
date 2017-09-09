#ifndef FRAMEBUILDER_HPP
#define FRAMEBUILDER_HPP

#include <QObject>
#include "EQThread.hpp"
#include <QByteArray>
#include <QSharedPointer>
#include "Frame.hpp"

class FrameBuilder : public EQThread
{
    Q_OBJECT
public:
    FrameBuilder();
    virtual ~FrameBuilder(){}

public slots:
    virtual void ByteReaded(QByteArray ba) = 0;
    virtual void FrameWrite(QSharedPointer<Frame> fr) = 0;
    virtual void PureDataWrite(QByteArray ba) = 0;

signals:
    void Write(QSharedPointer<Frame>);
    void FrameReaded(QSharedPointer<Frame>);
    void Error(QString);
};

#endif
