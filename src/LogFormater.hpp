#ifndef LOGFORMATER_HPP
#define LOGFORMATER_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include "Frame.hpp"

class LogFormater : public QObject
{
    Q_OBJECT
public:
    LogFormater(){}
    virtual ~LogFormater(){}

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame) = 0;
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;

signals:
    void Error(QString msg);
    void LogUIString(QString str, bool dirin);
    void LogFileString(QString str);
};

#endif
