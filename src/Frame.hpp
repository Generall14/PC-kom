#ifndef FRAME_HPP
#define FRAME_HPP

#include <QString>
#include <QByteArray>

class Frame
{
    Frame(){}
public:
    Frame(QByteArray data);
    virtual ~Frame(){}

    virtual bool isValid() = 0;
    virtual QString toQString() = 0;

    QByteArray pureData();

protected:
    QByteArray pck;
};

#endif
