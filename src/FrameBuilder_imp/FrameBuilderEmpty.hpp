#ifndef FRAMEBUILDEREMPTY_HPP
#define FRAMEBUILDEREMPTY_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"

class FrameBuilderEmpty : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderEmpty();
    virtual ~FrameBuilderEmpty(){}

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
};

#endif
