#include "MendiumEcho.hpp"

MendiumEcho::MendiumEcho()
{
    Desc::description = "MediumEcho";
}

MendiumEcho::~MendiumEcho()
{

}

void MendiumEcho::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumEcho::Close()
{
    opened = false;
    emit Closed();
}

void MendiumEcho::Write(QSharedPointer<Frame> fr)
{
    emit Readed(fr->pureData());
}

void MendiumEcho::Flush()
{

}

void MendiumEcho::Run()
{
    QThread::msleep(1000);
}
