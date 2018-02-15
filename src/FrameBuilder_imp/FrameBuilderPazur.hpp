#ifndef FRAMEBUILDERPAZUR_HPP
#define FRAMEBUILDERPAZUR_HPP

#include "../FrameBuilder.hpp"
#include <QObject>
#include <QSharedPointer>
#include "../Frame.hpp"
#include <QTimer>
#include <QMutex>

class FrameBuilderPazur : public FrameBuilder
{
    Q_OBJECT
public:
    FrameBuilderPazur();
    virtual ~FrameBuilderPazur();

public slots:
    virtual void ByteReaded(QByteArray ba);
    virtual void FrameWrite(QSharedPointer<Frame> fr);
    virtual void PureDataWrite(QByteArray ba);

protected:
    virtual void Run();
    QTimer* timer = nullptr;
    QMutex mutex;

    QByteArray trash;
    QByteArray potentialFrame;
    int collectingBytes = 0;

protected slots:
    void TimeoutedReciev();
};

#endif
