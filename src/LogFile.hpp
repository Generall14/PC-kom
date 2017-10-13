#ifndef LOGFILE_HPP
#define LOGFILE_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame.hpp"

class LogFile : public QObject
{
    Q_OBJECT
public:
    LogFile(){}
    virtual ~LogFile(){}

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame) = 0;
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;
};

#endif
