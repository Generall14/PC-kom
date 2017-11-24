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

    bool isValid() const;
    bool DoYouNeedThis(method met);
    void Add(method met);

    method ask;
    method answer;
    QList<QByteArray> values;
};

#endif
