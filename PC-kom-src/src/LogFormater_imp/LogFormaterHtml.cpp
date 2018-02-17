#include "LogFormaterHtml.hpp"
#include <QTime>

LogFormaterHtml::LogFormaterHtml()
{
    Desc::description = "LogFormaterHtml";
}

void LogFormaterHtml::FrameWrite(QSharedPointer<Frame> frame)
{
    QString temps = "<font face=\"Hack\" color=#00b3b3><b>PC ---> DEV ";
    QString templ = QTime::currentTime().toString("HH:mm:ss");
    temps += templ;
    templ.insert(0, "PC ---> DEV ");
    temps += ": </b></font>";
    if(!frame->isValid())
        temps += "<font face=\"Hack\" color=\"red\">";
    temps += frame->toQString();
    templ.append("  " + frame->toQString());
    if(!frame->isValid())
        temps += "</font>";

    emit LogUIString(temps, true);
    emit LogFileString(templ);
}

void LogFormaterHtml::FrameReaded(QSharedPointer<Frame> frame)
{
    QString temps = "<font face=\"Hack\" color=#b300b3><b>PC &#60;--- DEV ";
    QString templ = QTime::currentTime().toString("HH:mm:ss");
    temps += templ;
    templ.insert(0, "PC <--- DEV ");
    temps += ": </b></font>";
    if(!frame->isValid())
        temps += "<font face=\"Hack\" color=\"red\">";
    temps += frame->toQString();
    templ.append("  " + frame->toQString());
    if(!frame->isValid())
        temps += "</font>";

    emit LogUIString(temps, false);
    emit LogFileString(templ);
}

void LogFormaterHtml::FrameIgnored(QSharedPointer<Frame> frame)
{
    QString temps = "<font face=\"Hack\" color=#999999><b>-&#60;->-&#60;->-- ";
    QString templ = QTime::currentTime().toString("HH:mm:ss");
    temps += templ;
    templ.insert(0, "SMW <-> S ");
    temps += ": </b></font>";
    if(!frame->isValid())
        temps += "<font face=\"Hack\" color=\"red\">";
    temps += frame->toQString();
    templ.append("  " + frame->toQString());
    if(!frame->isValid())
        temps += "</font>";

    emit LogUIString(temps, false);
    emit LogFileString(templ);
}
