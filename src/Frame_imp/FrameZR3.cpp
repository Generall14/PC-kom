#include "FrameZR3.hpp"

FrameZR3::FrameZR3(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameZR3";
}

bool FrameZR3::isValid()
{
    return true;
}

QString FrameZR3::toQString()
{
    return "dupa";
}

QString FrameZR3::toShortQString()
{
    return "XXX";
}

QByteArray FrameZR3::magicNumbers()
{
    return "XXX";
}
