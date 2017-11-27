#ifndef TRANSACTIONDESCRIPTION_HPP
#define TRANSACTIONDESCRIPTION_HPP

#include <QList>
#include <QByteArray>
#include "method.hpp"

class TransactionDesc
{
public:
    TransactionDesc(method iask, method ianswer);
    TransactionDesc(method met);
    TransactionDesc();

    bool isValid() const;
    bool DoYouNeedThis(method met);
    void Add(method met);

    method ask;
    method answer;
    int attempts; // liczba prób wykonania transakcji
    int currentTime; // aktualny czas od zapytania
};

#endif
