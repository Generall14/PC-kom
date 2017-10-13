#ifndef LOGFILEDEFAULT_HPP
#define LOGFILEDEFAULT_HPP

#include <QFrame>
#include "../LogFile.hpp"
#include <QSharedPointer>
#include "../Frame.hpp"

class LogFileDefault : public LogFile
{
    Q_OBJECT
public:
    LogFileDefault();

public slots:
    virtual void FrameWrite(QSharedPointer<Frame>);
    virtual void FrameReaded(QSharedPointer<Frame>);
};

#endif
