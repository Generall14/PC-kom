#include "FrameEmpty.hpp"

FrameEmpty::FrameEmpty(QByteArray ba)
    :Frame(ba)
{
    Desc::description = "FrameEmpty";
}

bool FrameEmpty::isValid()
{
    return true;
}

QString FrameEmpty::toQString()
{
    return "Nic tu nie ma - to tylko testowa implementacja klasy Frame";
}

QString FrameEmpty::toShortQString()
{
    return "XXX";
}

QByteArray FrameEmpty::magicNumbers()
{
    return "XXX";
}
