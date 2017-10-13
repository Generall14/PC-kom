#include "Frame.hpp"
#include <QDebug>

Frame::Frame(QByteArray data)
{
    pck = data;
}

Frame::~Frame()
{
}

QByteArray Frame::pureData()
{
    return pck;
}
