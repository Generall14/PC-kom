#ifndef FRAMEBUILDERZR3_HPP
#define FRAMEBUILDERZR3_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include <QTimer>
#include <QList>
#include <QMutex>
#include "../Frame.hpp"

class FrameBuilderZR3 : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderZR3(uchar myAdr=0xFE, uchar nextAdr=0x01, bool slw=true);
    virtual ~FrameBuilderZR3();

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    virtual void OnStart();
    uchar _myAdr;
    uchar _nextAdr;
    bool _slowly;
    bool haveToken = false;

    QByteArray tokenFrame;
    QTimer* tokenTimer = NULL;

    QTimer* timer = NULL;
    QByteArray recievedbuf;

    QList<Frame*> inBuffor;
    QMutex inBufforMutex;
    void ReadInputBuffer();

    QList<Frame*> outBuffor;
    QMutex outBufforMutex;
    void sendOutputBuffer();

    static const int STANDARD_TOKEN_TIME_MS = 10;
    static const int SLOWLY_TOKEN_TIME_MS = 1000;
    static const int BYTE_TIME_US = 87;

protected slots:
    void TimeoutedReciev();
    void TokenTimerTimeout();
};

#endif
