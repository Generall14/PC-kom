#ifndef FRAMEBUILDERZR3_HPP
#define FRAMEBUILDERZR3_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"

class FrameBuilderZR3 : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderZR3();
    virtual ~FrameBuilderZR3(){}

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
};

#endif
