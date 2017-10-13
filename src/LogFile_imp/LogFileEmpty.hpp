#ifndef LOGFILEEMPTY_HPP
#define LOGFILEEMPTY_HPP

#include <QFrame>
#include "../LogFile.hpp"
#include <QSharedPointer>
#include "../Frame.hpp"

class LogFileEmpty : public LogFile
{
    Q_OBJECT
public:
    LogFileEmpty();

public slots:
    virtual void FrameWrite(QSharedPointer<Frame>);
    virtual void FrameReaded(QSharedPointer<Frame>);
};

#endif
