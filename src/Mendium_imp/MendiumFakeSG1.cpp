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

    QByteArray pck = frame->pureData();

    if((pck[0]&0xF0)==0x00)
    {
        int nr = pck.at(0)&0x0F;
        if(nr>11)
            return;
        if(vReadReq.indexOf(nr)!=-1)
            return;
        vReadReq.append(nr);
    }

    if((pck[0]&0xF0)==0x20)
    {
        int nr = pck.at(0)&0x0F;
        if(nr>11)
            return;
        int tempval = 0;
        tempval |= (pck.at(1)<<16)&0xFF0000;
        tempval |= (pck.at(2)<<8)&0x00FF00;
        tempval |= (pck.at(3)<<0)&0x0000FF;
        vConfig[nr] = tempval;
    }

    switch(pck.at(0))
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
    case 's':
        arep = pck.at(3);
        return;
    }
    errreq = true;
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
        while(!vReadReq.isEmpty())
        {
            SendFrame(vReadReq.at(0)|0x10, vConfig.at(vReadReq.at(0)));
            vReadReq.remove(0);
        }
        if(errreq)
            SendFrame('E', errNumbers.at(qrand()%errNumbers.size()));
        errreq = false;
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
