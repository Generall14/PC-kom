#include "Frame.hpp"
#include <QDebug>

Frame::Frame(QByteArray data)
{
    pck = data;
    Desc::description = "Czysta abstrakcja Frame";
}

Frame::~Frame()
{
}

QByteArray Frame::pureData()
{
    return pck;
}

QByteArray Frame::srcAdr()
{
    return QByteArray();
}

QByteArray Frame::dstAdr()
{
    return QByteArray();
}

QByteArray Frame::aplData()
{
    return QByteArray();
}
