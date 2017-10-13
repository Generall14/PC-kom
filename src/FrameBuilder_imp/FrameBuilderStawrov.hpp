#ifndef FRAMEBUILDERSTAWROV_HPP
#define FRAMEBUILDERSTAWROV_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include "../Frame.hpp"

class FrameBuilderStawrov : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderStawrov();
    virtual ~FrameBuilderStawrov();

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    QTimer* timer = NULL;
    QByteArray recievedbuf;

protected slots:
    void TimeoutedReciev();
};

#endif
