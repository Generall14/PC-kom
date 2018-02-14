#ifndef FRAMEBUILDERTERMINAL_HPP
#define FRAMEBUILDERTERMINAL_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"
#include <QTimer>

class FrameBuilderTerminal : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderTerminal();
    virtual ~FrameBuilderTerminal();

    static uint getTimeoutMs();
    static uint getPckSize();
    static void setTimeoutMs(uint val);
    static void setPckSize(uint val);

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    QTimer* timer = nullptr;
    QByteArray recievedbuf;

    static uint _timeoutMs;
    static uint _countTo;

protected slots:
    void TimeoutedReciev();
};

#endif
