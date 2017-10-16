#include "LogFileDefault.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QTextStream>
#include <QFileInfo>

LogFileDefault::LogFileDefault()
{
    Desc::description = "LogFileDefault";

    QDir cdir("./logs/");
    if (!cdir.exists())
        cdir.mkpath(".");

    lastFile.setFileName(GenerateFileName());
}

LogFileDefault::~LogFileDefault()
{
    Flush();
}

void LogFileDefault::LogString(QString str)
{
    buffor.append(str);
    if(buffor.size()>BUFFOR_SIZE_TR)
        Flush();
}

QString LogFileDefault::GenerateFileName()
{
    return "logs/LogFileDefault_" + QDate::currentDate().toString("yyyy-MM-dd") + QTime::currentTime().toString("_HH-mm-ss") + ".log";
}

void LogFileDefault::Flush()
{
    if(buffor.isEmpty())
        return;

    if(lastFile.open(QIODevice::Append | QIODevice::Text | QIODevice::WriteOnly))
    {
        QTextStream out(&lastFile);
        for(QString sstr: buffor)
            out << sstr + "\n";
        lastFile.close();
    }
    else
        emit Error("Nie można pisać do pliku \"" + lastFile.fileName() + "\"");

    buffor.clear();

    QFileInfo fi(lastFile);
    if((fi.size()>MAX_FILE_BYTES)||(fi.size()==0))
        lastFile.setFileName(GenerateFileName());
}
