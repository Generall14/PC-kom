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
