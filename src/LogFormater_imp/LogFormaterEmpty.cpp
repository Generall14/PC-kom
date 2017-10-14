#include "LogFormaterEmpty.hpp"

LogFormaterEmpty::LogFormaterEmpty()
{

}

void LogFormaterEmpty::FrameWrite(QSharedPointer<Frame> frame)
{
    emit LogUIString("Out: " + frame->toQString(), true);
    emit LogFileString(frame->toQString());
}

void LogFormaterEmpty::FrameReaded(QSharedPointer<Frame> frame)
{
    emit LogUIString("In: " + frame->toQString(), false);
    emit LogFileString(frame->toQString());
}
