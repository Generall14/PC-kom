#include "Frame.hpp"
#include <QDebug>

Frame::Frame(QByteArray data)
{
    pck = data;
    qDebug() << "konstruktor Frame";
}

Frame::~Frame()
{
    qDebug() << "destruktor Frame";
}

QByteArray Frame::pureData()
{
    return pck;
}
