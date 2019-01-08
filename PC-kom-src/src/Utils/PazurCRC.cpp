#include "PazurCRC.hpp"
#include <stdexcept>

#include <QString>
#include <QDebug>

void PazurCRC::AppendCRC5(QByteArray& header)
{
    if(header.size()<4)
        throw std::runtime_error("PazurCRC::AppendCRC5: wtf?");
    header[3] = (header.at(3)&0x83) | CalcCRC5(header)<<2;
}

/**
 * Sprawdza poprawność crc we wskazanym nagłowku.
 * @return true - suma CRC jest zgodna.
 */
bool PazurCRC::CheckCRC5(QByteArray& header)
{
    if(header.size()<4)
        throw std::runtime_error("PazurCRC::CheckCRC5: wtf?");
    uint8_t crca = (header.at(3)>>2)&0x1f;
    uint8_t crcb = CalcCRC5(header);
    return crca==crcb;
}

std::shared_ptr<uint8_t> PazurCRC::makeCrc5tableLsbFirst(uint8_t poly)
{
    poly &= 0x1F;

    uint8_t npoly = 0;
    for(int b=0;b<5;++b)
    {
        if(poly&(1<<b))
            npoly |= 0x10>>b;
    }
    poly = npoly;

    std::shared_ptr<uint8_t> sp(new uint8_t[16], std::default_delete<uint8_t[]>());
    for(int i=0;i<16;++i)
    {
        int r = i;
        for(int j=0;j<4;++j)
        {
            if((r&0x01)!=0)
                r = (r>>1)^poly;
            else
                r>>=1;
        }
        sp.get()[i] = r&0x1f;
    }
    return sp;
}


char PazurCRC::CalcCRC5(QByteArray& header)
{
    if(header.size()<4)
        throw std::runtime_error("PazurCRC::CalcCRC5: wtf?");
    uint8_t poly = 0x1D;
    uint8_t sum = 0x14;

    auto sp = makeCrc5tableLsbFirst(poly);

    for(int i=0;i<3;++i)
    {
        uint8_t lval = header[i];

        uint8_t arrPtr = sum&0x0F;
        sum = (sum>>4)&0x01;
        sum |= (lval<<1)&0x1E;
        sum ^= sp.get()[arrPtr];

        arrPtr = sum&0x0F;
        sum = (sum>>4)&0x01;
        sum |= (lval>>3)&0x1E;
        sum ^= sp.get()[arrPtr];
    }

    uint8_t lval = header[3];
    uint8_t arrPtr = (sum<<2)&0x0c;
    sum = (sum>>2)&0x07;
    sum |= (lval<<3)&0x18;
    sum ^= sp.get()[arrPtr];

    arrPtr = sum&0x0F; // dodatkowa połówka do wypchnięcia CRC
    sum = (sum>>4)&0x01;
    sum ^= sp.get()[arrPtr];

    arrPtr = sum&0x01; // ostatni bit do wypchnięcia CRC
    sum = (sum>>1)&0x0F;
    sum ^= sp.get()[arrPtr<<3];

    return sum&0x1F;
}
