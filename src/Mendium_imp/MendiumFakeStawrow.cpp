#include "MendiumFakeStawrow.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include <QDebug>

MendiumFakeStawrow::MendiumFakeStawrow()
{
    Desc::description = "MendiumFakeStawrow";

    sdata.clear();
    sdata.append(0xFF);
    sdata.append(0xF9);
}

void MendiumFakeStawrow::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumFakeStawrow::Close()
{
    opened = false;
    emit Closed();
}

void MendiumFakeStawrow::Write(QSharedPointer<Frame>)
{

}

void MendiumFakeStawrow::Flush()
{

}

void MendiumFakeStawrow::Run()
{
    QThread::msleep(200);
    if(opened)
    {
        char status = 0x00;
        if(occupied)
            status |= 0x01;
        if(!(qrand()%20))
            occupied = !occupied;
        const int channels = 6;
        QByteArray temp(sdata);
        temp.append(channels*2+3);
        temp.append(0xFF);
        temp.append(0x31);
        temp.append(status);
        temp.append((char)0x00);
        for(int i=0;i<channels;i++)
        {
            int tint = qrand()%1000;
            temp.append(tint&0xFF);
            temp.append((tint>>8)&0xFF);
        }
        temp = FrameStawrov::AddCRC16(temp);
        emit Readed(temp);
    }
}
