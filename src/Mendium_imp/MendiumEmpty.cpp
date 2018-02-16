#include "MendiumEmpty.hpp"
#include <QDebug>

MendiumEmpty::MendiumEmpty()
{
    Desc::description = "MendiumEmpty";
}

void MendiumEmpty::Open(QString)
{
    opened = true;
    emit Opened();
}

void MendiumEmpty::Close()
{
    opened = false;
    emit Closed();
}

void MendiumEmpty::Write(QSharedPointer<Frame>)
{

}

void MendiumEmpty::Flush()
{

}

void MendiumEmpty::Run()
{
    QThread::msleep(1000);
    if(opened)
    {
        QByteArray temp("Testowa odpowiedz medium.");
        emit Readed(temp);
    }
}
