#ifndef FRAMEBUILDERSPROT_HPP
#define FRAMEBUILDERSPROT_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"
#include <QTimer>

class FrameBuilderSProt : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderSProt();
    virtual ~FrameBuilderSProt();

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    QTimer* timer = nullptr;
    QByteArray recievedbuf;

    static uint _timeoutMs;
    static int _countTo;

protected slots:
    void TimeoutedReciev();
};

#endif
