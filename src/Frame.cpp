#include "Frame.hpp"

Frame::Frame(QByteArray data)
{
    pck = data;
}

QByteArray Frame::pureData()
{
    return pck;
}
