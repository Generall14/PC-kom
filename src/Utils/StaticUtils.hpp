#ifndef STATICUTILS_HPP
#define STATICUTILS_HPP

#include <QByteArray>

class SU
{
public:
    static float float24to32(QByteArray b);
    static QByteArray float32to24(float f);
    static float byteArray2Float32(QByteArray b);
    static QByteArray float32toByteArray(float f);

private:
    union FI;
};

#endif
