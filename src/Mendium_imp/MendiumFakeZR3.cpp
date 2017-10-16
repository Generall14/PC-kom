#include "MendiumFakeZR3.hpp"
#include <QDebug>

MendiumFakeZR3::MendiumFakeZR3()
{
    Desc::description = "MendiumFakeZR3";
}

void MendiumFakeZR3::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumFakeZR3::Close()
{
    opened = false;
    emit Closed();
}

void MendiumFakeZR3::Write(QSharedPointer<Frame>)
{

}

void MendiumFakeZR3::Flush()
{

}

void MendiumFakeZR3::Run()
{
    QThread::msleep(100);
    if(opened)
    {

    }
}
