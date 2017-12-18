#include "WorkerRead.hpp"

WorkerRead::WorkerRead(uchar offset, int timeout, int repeates):
    Worker(QByteArray(), timeout, repeates),
    _offset(offset)
{
    QByteArray temp;
    temp.append(0x78);
    temp.append(offset);
    temp.append(0xaa);
    temp.append(0x55);
    temp.append(~0x78);
    this->setDataToSend(temp);
}

WorkerRead::~WorkerRead()
{

}

bool WorkerRead::isItOk(QByteArray frame)
{
    if(frame.length()!=5)
        return false;

    if(frame.at(0)!=(char)(0x58))
        return false;

    if(frame.at(1)!=_offset)
        return false;

    return true;
}
