#ifndef CRC_HPP
#define CRC_HPP

#include <stdint.h>
#include <QByteArray>

class CRC
{
public:
    static uint8_t crc5(QByteArray arr, uint8_t sum = 0x05, uint8_t poly=0x1D, bool lsbFirst=true, bool reversedCrc=true);
private:
    CRC(){}
};

#endif
