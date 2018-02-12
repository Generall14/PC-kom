#include "TransactionMaker.hpp"
#include <QCoreApplication>
#include <QDebug>

TransactionMaker::TransactionMaker()
{
}

TransactionMaker::~TransactionMaker()
{

}

void TransactionMaker::OnStop()
{

}

void TransactionMaker::OnStart()
{

}

void TransactionMaker::RecievedData(QByteArray data)
{
    QMutexLocker locker(&mutex);
    for(int i=list.size()-1;i>=0;--i)
    {
        if(list[i].answer.header==data.at(0))
        {
            emit Done(data.at(0), data.mid(1));
            list.removeAt(i);
            break;
        }
    }
    locker.unlock();
}

void TransactionMaker::RegisterTransaction(TransactionDesc desc)
{
    desc.attempts = 0;
    QMutexLocker locker(&mutex);
    list.append(desc);
    SendAsk(list[list.size()-1]);
}

void TransactionMaker::SendAsk(TransactionDesc& tr)
{
    QByteArray temp;
    temp.append(tr.ask.header);
    temp.append(tr.ask.data);
    emit SendDataFrame(temp);
    tr.currentTime=tr.answer.timeout;
    tr.attempts++;
}

void TransactionMaker::Run()
{
    QThread::msleep(200);

    QMutexLocker locker(&mutex);
    for(int i=list.size()-1;i>=0;--i)
    {
        if(list[i].attempts>MAX_MISSES)
        {
            emit Error("Nieudana transakcja " + list.at(i).answer.tooltip);
            list.removeAt(i);
        }
        else
        {
            list[i].currentTime-=200;
            if(list[i].currentTime<=0)
                SendAsk(list[i]);
        }
    }
    locker.unlock();

    QCoreApplication::processEvents();
}
