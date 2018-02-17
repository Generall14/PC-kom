#include "CRC.hpp"
#include <assert.h>

/**
 * Oblicza crc5 sposobem łopatologicznym, nie nadaje się do rekurencyjnego doliczania crc, uzupełnia wejściowy ciąg danych o bajty zerowe
 * przepychające crc.
 * @param arr - dane wejściowe.
 * @param sum - początkowa wartość sumy.
 * @param poly - wielomian.
 * @param lsbFirst - false: bity bajtów danych będą pompowane zaczynając od najbardziej znaczących.
 * @param reversedCrc - true: po zakończeniu obliczeń zostanie zamieniona kolejność bitów sumy crc.
 * @return wynik obliczeń.
 */
uint8_t CRC::crc5(QByteArray arr, uint8_t sum, uint8_t poly, bool lsbFirst, bool reversedCrc)
{
    poly &= 0x1F;
    assert(arr.size()>0);
    assert(poly!=0);

    if(reversedCrc)
    {
        uint8_t ncrc = 0;
        for(int i=0;i<5;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x10>>i;
        }
        sum = ncrc;
    }

    for(int i=0;i<arr.length();++i)
    {
        uint8_t lval = arr.at(i);
        for(int i=0;i<8;++i)
        {
            bool needxor = sum&0x10;
            sum <<= 1;

            if(!lsbFirst)
            {
                if(lval&0x80)
                    sum |= 0x01;
                lval <<= 1;
            }
            else
            {
                if(lval&0x01)
                    sum |= 0x01;
                lval >>= 1;
            }

            if(needxor)
                sum ^= poly;
        }
    }

    for(int i=0;i<5;++i) // dodatkowe 5 bitów do wypchnięcia CRC
    {
        bool needxor = sum&0x10;
        sum <<= 1;
        if(needxor)
            sum ^= poly;
    }

    if(reversedCrc)
    {
        uint8_t ncrc = 0;
        for(int i=0;i<5;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x10>>i;
        }
        sum = ncrc;
    }

    return sum&0x1F;
}
