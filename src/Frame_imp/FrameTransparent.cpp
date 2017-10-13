#include "FrameTransparent.hpp"

FrameTransparent::FrameTransparent(QByteArray ba)
    :Frame(ba)
{}

bool FrameTransparent::isValid()
{
    return true;
}

QString FrameTransparent::toQString()
{
    QString temp;
    for(auto s: pck)
        temp.append(QString("0x%1 ").arg(((int)(s))&0xFF, 2, 16, QChar('0')));
    temp.remove(temp.size()-1, 1);
    temp = temp.toUpper();
    temp = temp.replace("X", "x");
    return temp;
}

QString FrameTransparent::toShortQString()
{
    return "XXX";
}

QByteArray FrameTransparent::magicNumbers()
{
    return "XXX";
}
