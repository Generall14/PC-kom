#ifndef LOGFORMATERHTML_HPP
#define LOGFORMATERHTML_HPP

#include <QFrame>
#include <QSharedPointer>
#include "../Frame.hpp"
#include "../LogFormater.hpp"

class LogFormaterHtml : public LogFormater
{
    Q_OBJECT
public:
    LogFormaterHtml();

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame);
    virtual void FrameReaded(QSharedPointer<Frame> frame);
    virtual void FrameIgnored(QSharedPointer<Frame> frame);
};

#endif
