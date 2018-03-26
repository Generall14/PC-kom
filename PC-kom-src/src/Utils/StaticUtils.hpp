#ifndef STATICUTILS_HPP
#define STATICUTILS_HPP

#include <QByteArray>
#include <QString>

class SU
{
public:
    static float float24to32(QByteArray b);
    static QByteArray float32to24(float f);

    static float byteArray2Float32(QByteArray b);
    static QByteArray float32toByteArray(float f);

    static int byteArray2Int16(QByteArray b);
    static QByteArray int16ToByteArray(int i);

    static int byteArray2Int32(QByteArray b);
    static QByteArray int32ToByteArray(int i);

    static uint64_t byteArray2Int48(QByteArray b);
    static QByteArray int48ToByteArray(long long i);

    static bool byteArray2bool(QByteArray b);
    static QByteArray boolToByteArray(bool b);

    static QByteArray string2ByteArray(QString str);
    static QString byteArray2String(QByteArray arr);

private:
    union FI;
};

#endif
