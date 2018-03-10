#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <QByteArray>
#include <QList>
#include <QString>
#include "Message.hpp"

class Messages
{
public:
    Messages(QByteArray dat, int siz, char addcrc);
    Messages(QList<Message> msgs);
    Messages();

    QString toQString() const;
    QByteArray toPureData() const;
    char addCrc10() const;

private:
    QByteArray _dat;
    bool isValid = false;
    bool isEmpty = false;
    QString errorMessage;
    char _addcrc;

    QList<Message> _msgs;
};

#endif
