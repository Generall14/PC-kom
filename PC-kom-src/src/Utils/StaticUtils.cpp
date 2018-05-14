#include "StaticUtils.hpp"

union SU::FI
{
    float f;
    int i;
};

float SU::float24to32(QByteArray b)
{
    if(b.size()<3)
        return -1;
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
    if(b.size()<4)
        return -1;
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

int SU::byteArray2Int16(QByteArray b)
{
    if(b.size()<2)
        return -1;
    int i=0;
    i |= (b.at(0)&0xFF)<<8;
    i |= (b.at(1)&0xFF)<<0;
    return i;
}

QByteArray SU::int16ToByteArray(int i)
{
    QByteArray temp;
    temp.append((i>>8)&0xFF);
    temp.append((i>>0)&0xFF);
    return temp;
}

int SU::byteArray2Int32(QByteArray b)
{
    if(b.size()<4)
        return -1;
    int i=0;
    i |= (b.at(0)&0xFF)<<24;
    i |= (b.at(1)&0xFF)<<16;
    i |= (b.at(2)&0xFF)<<8;
    i |= (b.at(3)&0xFF)<<0;
    return i;
}

QByteArray SU::int32ToByteArray(int i)
{
    QByteArray temp;
    temp.append((i>>24)&0xFF);
    temp.append((i>>16)&0xFF);
    temp.append((i>>8)&0xFF);
    temp.append((i>>0)&0xFF);
    return temp;
}

uint64_t SU::byteArray2Int48(QByteArray b)
{
    if(b.size()<6)
        return -1;
    uint64_t i=0;
    i |= ((uint64_t)(b.at(0)&0xFF))<<40;
    i |= ((uint64_t)(b.at(1)&0xFF))<<32;
    i |= (b.at(2)&0xFF)<<24;
    i |= (b.at(3)&0xFF)<<16;
    i |= (b.at(4)&0xFF)<<8;
    i |= (b.at(5)&0xFF)<<0;
    return i;
}

QByteArray SU::int48ToByteArray(long long i)
{
    QByteArray temp;
    temp.append((i>>40)&0xFF);
    temp.append((i>>32)&0xFF);
    temp.append((i>>24)&0xFF);
    temp.append((i>>16)&0xFF);
    temp.append((i>>8)&0xFF);
    temp.append((i>>0)&0xFF);
    return temp;
}

bool SU::byteArray2bool(QByteArray b)
{
    if(b.isEmpty())
        return false;
    if(b.at(0)&0x01)
        return true;
    else
        return false;
}

QByteArray SU::boolToByteArray(bool b)
{
    QByteArray temp;
    char t = 0x00;
    if(b)
        t |= 0x01;
    temp.append(t);
    return temp;
}

QByteArray SU::string2ByteArray(QString str)
{
    QByteArray temp;
    str.remove(' ');
    bool ok;
    int val;
    while(!str.isEmpty())
    {
        val = str.mid(0, 2).toInt(&ok, 16);
        if(!ok)
            return QByteArray();
        temp.push_back((char)val);
        str = str.mid(2);
    }
    return temp;
}

QString SU::byteArray2String(QByteArray arr)
{
    QString str;
    for(auto a: arr)
        str.append(QString("%1 ").arg(a&0xFF, 2, 16, QChar('0')));
    return str;
}

/**
 * Zamienia float32 na ciąg bajtów (little endian).
 */
QByteArray SU::float322ByteArray(float f)
{
    SU::FI temp;
    temp.f = f;
    QByteArray ta;
    ta.append((temp.i>>0)&0xFF);
    ta.append((temp.i>>8)&0xFF);
    ta.append((temp.i>>16)&0xFF);
    ta.append((temp.i>>24)&0xFF);
    return ta;
}

/**
 * Odczytuje ciąg bajtów (little endian) i zamienia je na float32.
 */
float SU::byteArray322Float32(QByteArray b)
{
    if(b.size()!=4)
        return -1.0;
    SU::FI temp;
    temp.i = 0;
    temp.i |= (b.at(0)<<0)&0xFF;
    temp.i |= (b.at(1)<<8)&0xFF00;
    temp.i |= (b.at(2)<<16)&0xFF0000;
    temp.i |= (b.at(3)<<24)&0xFF000000;
    return temp.f;
}

QString SU::displayFloat(float f, uint precision)
{
    float s = 1;
    if(f<0)
        s = -1;
    f *= s;
    QString pre = "jhgj";
    if(f>1e9)
    {
        pre = "G";
        f /= 1e9;
    }
    else if(f>1e6)
    {
        pre = "M";
        f /= 1e6;
    }
    else if(f>1e3)
    {
        pre = "K";
        f /= 1e3;
    }
    else if(f<1e-9)
    {
        pre = "p";
        f *= 1e12;
    }
    else if(f<1e-6)
    {
        pre = "n";
        f *= 1e9;
    }
    else if(f<1e-3)
    {
        pre = "u";
        f *= 1e6;
    }
    else if(f<1)
    {
        pre = "m";
        f *= 1e3;
    }
    f *= s;
    return QString::number(f, 'g', precision)+" "+pre;
}
