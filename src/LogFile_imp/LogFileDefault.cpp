#include "LogFileDefault.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

LogFileDefault::LogFileDefault()
{
    QDir cdir("./logs/");
    if (!cdir.exists())
        cdir.mkpath(".");
}

void LogFileDefault::LogString(QString str)
{

}
