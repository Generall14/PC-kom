#ifndef LOGFORMATEREMPTY_HPP
#define LOGFORMATEREMPTY_HPP

#include <QFrame>
#include <QSharedPointer>
#include "../Frame.hpp"
#include "../LogFormater.hpp"

class LogFormaterEmpty : public LogFormater
{
    Q_OBJECT
public:
    LogFormaterEmpty();

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame);
    virtual void FrameReaded(QSharedPointer<Frame> frame);
};

#endif
