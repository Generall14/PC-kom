#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <QSharedPointer>
#include <QByteArray>
#include "../../Frame.hpp"

struct transaction
{
    transaction(){}
    transaction(QSharedPointer<Frame> frame, QByteArray resp, int timeoutms, int repeates):
        sendFrame(frame),
        timeout(timeoutms),
        maxrepeate(repeates),
        requestedMagisNumber(resp){}
    QSharedPointer<Frame> sendFrame;
    int timeout;
    int maxrepeate;
    QByteArray requestedMagisNumber;
};

#endif
