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

    void FromQByteArray(QByteArray ba);
    int ReadTimeout();
    int WriteTimeout();
    int FrameLength();

    virtual bool isValid() = 0;
    virtual QString toQString() = 0;

protected:
    QByteArray pck;
    int rTimeout=2000;
    int wTimeout=2000;
    int frameLength=1;
};

#endif
