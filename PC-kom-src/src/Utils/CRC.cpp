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
    sum &= 0x1F;
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

uint8_t CRC::crc8(QByteArray arr, uint8_t sum, uint8_t poly, bool lsbFirst, bool reversedCrc)
{
    poly &= 0xFF;
    sum &= 0xFF;
    assert(arr.size()>0);
    assert(poly!=0);

    if(reversedCrc)
    {
        uint8_t ncrc = 0;
        for(int i=0;i<8;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x80>>i;
        }
        sum = ncrc;
    }

    for(int i=0;i<arr.length()+1;++i)// dla każdego bajtu danych plus jeden bajt do przepchnięcia
    {
        uint8_t lval = 0x00; // zerowy bajt do wypchnięcia CRC
        if(i<arr.length())
            lval = arr[i];
        for(int i=0;i<8;++i)
        {
            bool needxor = sum&0x80;
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

    if(reversedCrc)
    {
        uint8_t ncrc = 0;
        for(int i=0;i<8;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x80>>i;
        }
        sum = ncrc;
    }

    return sum&0xFF;
}

uint16_t CRC::crc10(QByteArray arr, uint16_t sum, uint16_t poly, bool lsbFirst, bool reversedCrc)
{
    poly &= 0x3FF;
    sum &= 0x3FF;
    assert(arr.size()>0);
    assert(poly!=0);

    if(reversedCrc)
    {
        uint16_t ncrc = 0;
        for(int i=0;i<10;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x200>>i;
        }
        sum = ncrc;
    }

    for(int i=0;i<arr.length();++i)
    {
        uint8_t lval = arr[i];
        for(int i=0;i<8;++i)
        {
            bool needxor = sum&0x200;
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

    for(int i=0;i<10;++i) // 10 dodatkowych bitów do wypchnięcia CRC
    {
        bool needxor = sum&0x200;
        sum <<= 1;
        if(needxor)
            sum ^= poly;
    }

    if(reversedCrc)
    {
        uint16_t ncrc = 0;
        for(int i=0;i<10;++i)
        {
            if(sum&(1<<i))
                ncrc |= 0x200>>i;
        }
        sum = ncrc;
    }

    return sum&0x3FF;
}
