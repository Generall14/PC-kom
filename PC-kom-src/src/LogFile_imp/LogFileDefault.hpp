#ifndef LOGFILEDEFAULT_HPP
#define LOGFILEDEFAULT_HPP

#include <QFrame>
#include "../LogFile.hpp"
#include <QSharedPointer>
#include <QFile>
#include "../Frame.hpp"

class LogFileDefault : public LogFile
{
    Q_OBJECT
public:
    LogFileDefault();
    ~LogFileDefault();

public slots:
    virtual void LogString(QString str);

protected:
    QStringList buffor;
    QFile lastFile;

    void Flush();
    QString GenerateFileName();

    static const int MAX_FILE_BYTES = 1*1024*1024;
    static const int BUFFOR_SIZE_TR = 20;
};

#endif
