#ifndef FRAMEBUILDERSG1_HPP
#define FRAMEBUILDERSG1_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"
#include <QTimer>

class FrameBuilderSG1 : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderSG1();
    virtual ~FrameBuilderSG1();

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    QTimer* timer = nullptr;
    QByteArray recievedbuf;

protected slots:
    void TimeoutedReciev();
};

#endif
