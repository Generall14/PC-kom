#include "StaticUtils.hpp"

union SU::FI
{
    float f;
    int i;
};

float SU::float24to32(QByteArray b)
{
    FI con;
    con.i &= 0x00;
    con.i |= (b[0]&0xFF)<<23;
    con.i |= (b[1]&0xFF)<<15;
    con.i |= (b[2]&0xFF)<<7;
    return con.f;
}

QByteArray SU::float32to24(float f)
{
    QByteArray temp;
    FI con;
    con.f = f;
    temp.push_back(char((con.i&0x7F800000)>>23));
    temp.push_back(char((con.i&0x7F8000)>>15));
    temp.push_back(char((con.i&0x7F80)>>7));
    return temp;
}

float SU::byteArray2Float32(QByteArray b)
{
    FI con;
    con.i &= 0x00;
    con.i |= (b[0]&0xFF)<<24;
    con.i |= (b[1]&0xFF)<<16;
    con.i |= (b[2]&0xFF)<<8;
    con.i |= (b[3]&0xFF)<<0;
    return con.f;
}

QByteArray SU::float32toByteArray(float f)
{
    QByteArray temp;
    FI con;
    con.f = f;
    temp.push_back(char((con.i&0xFF000000)>>24));
    temp.push_back(char((con.i&0x00FF0000)>>16));
    temp.push_back(char((con.i&0x0000FF00)>>8));
    temp.push_back(char((con.i&0x000000FF)>>0));
    return temp;
}
