#include "transactionDesc.hpp"
#include <qDebug>

TransactionDesc::TransactionDesc(method iask, method ianswer):
    ask(iask),
    answer(ianswer)
{

}

TransactionDesc::TransactionDesc(method met)
{
    ask.header=0x00;
    answer.header=0x00;
    ask.secondHeader=0xFF;
    answer.secondHeader=0xFF;
    ask.direct = true;
    answer.direct = true;
    if(met.direct)
    {
        ask.direct = false;
        answer.direct = false;
    }
    Add(met);
}

TransactionDesc::TransactionDesc()
{
    ask.header=0x00;
    answer.header=0x00;
    ask.secondHeader=0xFF;
    answer.secondHeader=0xFF;
    ask.direct = true;
    answer.direct = true;
}

bool TransactionDesc::isValid() const
{
    if((char)ask.secondHeader!=(char)answer.header)
        return false;
    if((char)ask.header!=(char)answer.secondHeader)
        return false;
    return true;
}

void TransactionDesc::Add(method met)
{
    if(met.direct)
        ask = met;
    else
        answer = met;
}

/**
 * Sprawdza czy brakuje jej podanej metody.
 */
bool TransactionDesc::DoYouNeedThis(method met)
{
    if(isValid())
        return false;

    method old;
    if(met.direct)
        old = answer;
    else
        old = ask;

    if(old.secondHeader!=met.header)
        return false;
    if(old.header!=met.secondHeader)
        return false;

    Add(met);

    return true;
}
