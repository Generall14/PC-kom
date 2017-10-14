#ifndef LOGFILE_HPP
#define LOGFILE_HPP

#include <QFrame>
#include <QString>
#include <QObject>

class LogFile : public QObject
{
    Q_OBJECT
public:
    LogFile(){}
    virtual ~LogFile(){}

public slots:
    virtual void LogString(QString str) = 0;

signals:
    void Error(QString msg);
};

#endif
