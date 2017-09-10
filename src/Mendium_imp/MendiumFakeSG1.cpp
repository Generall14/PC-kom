#include "MendiumFakeSG1.hpp"
#include <QDebug>

MendiumFakeSG1::MendiumFakeSG1()
{

}

void MendiumFakeSG1::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumFakeSG1::Close()
{
    opened = false;
    emit Closed();
}

void MendiumFakeSG1::Write(QSharedPointer<Frame> frame)
{
    if(!frame->isValid())
        return;

    switch(frame->pureData().at(0))
    {
    case 'h':
        helloreq = true;
        return;
    case 'v':
        battreq = true;
        return;
    case 'c':
        rrep |= 1<<shiftCnt;
        return;
    case 'd':
        rrep |= 1<<shiftDAC;
        return;
    case 't':
        rrep |= 1<<shiftTemp;
        return;
    case 'z':
        rrep |= 1<<shiftZatk;
        return;
    case 'l':
        rrep |= 1<<shiftLevels;
        return;
    }
}

void MendiumFakeSG1::Flush()
{

}

void MendiumFakeSG1::Run()
{
    QThread::msleep(500);
    if(opened)
    {
        if(helloreq)
            SendFrame('H', helloresp);
        if(battreq)
            SendFrame('V', qrand()%1024);

        if(  ((arep>>shiftCnt)&0x01)  ||  ((rrep>>shiftCnt)&0x01)  )
            SendFrame('C', qrand()%10);
        if(  ((arep>>shiftACal)&0x01)  ||  ((rrep>>shiftACal)&0x01)  )
            SendFrame('A', qrand()%10);
        if(  ((arep>>shiftDAC)&0x01)  ||  ((rrep>>shiftDAC)&0x01)  )
            SendFrame('D', qrand()%256);
        if(  ((arep>>shiftTemp)&0x01)  ||  ((rrep>>shiftTemp)&0x01)  )
            SendFrame('T', qrand()%1024);
        if(  ((arep>>shiftZatk)&0x01)  ||  ((rrep>>shiftZatk)&0x01)  )
            SendFrame('Z', qrand()%1024);
        if(  ((arep>>shiftLevels)&0x01)  ||  ((rrep>>shiftLevels)&0x01)  )
            SendFrame('L', 0x000106);
        rrep = 0;
        helloreq = false;
        battreq = false;
    }
}

void MendiumFakeSG1::SendFrame(char header, int val)
{
    QByteArray temp;
    temp.append(header);
    temp.append((val>>16)&0xFF);
    temp.append((val>>8)&0xFF);
    temp.append((val>>0)&0xFF);
    temp.append(((int)header)^0xFF);
    emit Readed(temp);
}
