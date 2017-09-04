#include "Frame.hpp"

Frame::Frame(QByteArray data)
{
    this->FromQByteArray(data);
}

void Frame::FromQByteArray(QByteArray ba)
{
    pck = ba;
}

int Frame::ReadTimeout()
{
    return rTimeout;
}

int Frame::WriteTimeout()
{
    return wTimeout;
}

int Frame::FrameLength()
{
    return frameLength;
}
