#ifndef PAZURCRC_HPP
#define PAZURCRC_HPP

#include <stdint.h>
#include <QByteArray>
#include <memory>

class PazurCRC
{
public:
    static void AppendCRC5(QByteArray& header);
    static bool CheckCRC5(QByteArray& header);

private:
    PazurCRC(){}
    static char CalcCRC5(QByteArray& header);
    static std::shared_ptr<uint8_t> makeCrc5tableLsbFirst(uint8_t poly);

};

#endif
