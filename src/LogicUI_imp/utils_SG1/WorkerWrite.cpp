#include "WorkerWrite.hpp"

WorkerWrite::WorkerWrite(uchar offset, QByteArray data, int timeout, int repeates):
    Worker(QByteArray(), timeout, repeates),
    _offset(offset),
    _data(data)
{
    QByteArray temp;
    temp.append(0x79);
    temp.append(offset);
    temp.append(data.at(0));
    temp.append(data.at(1));
    temp.append(~0x79);
    this->setDataToSend(temp);
}

WorkerWrite::~WorkerWrite()
{

}

bool WorkerWrite::isItOk(QByteArray frame)
{
    if(frame.length()!=5)
        return false;

    if(frame.at(0)!=(char)(0x58))
        return false;

    if(frame.at(1)!=_offset)
        return false;

    if(frame.at(2)!=_data.at(0))
        return false;

    if(frame.at(3)!=_data.at(1))
        return false;

    return true;
}
