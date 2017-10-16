#include "MendiumFakeStawrow.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include <QDebug>

MendiumFakeStawrow::MendiumFakeStawrow()
{
    Desc::description = "MendiumFakeStawrow";

    sdata.clear();
    sdata.append(0xFF);
    sdata.append(0xFF);
    sdata.append(0xFF);
    sdata.append(0x08);
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
    QThread::msleep(100);
    if(opened)
    {
        QByteArray temp(sdata);
        for(int i=0;i<4;i++)
        {
            int tint = qrand();
            temp.append((tint>>8)&0xFF);
            temp.append(tint&0xFF);
        }
        temp = FrameStawrov::AddCRC16(temp);
        emit Readed(temp);
    }
}
