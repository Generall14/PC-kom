#ifndef CONFIRMS_HPP
#define CONFIRMS_HPP

#include <QByteArray>
#include <QList>
#include <QString>
#include "Confirm.hpp"

class Confirms
{
public:
    Confirms(QByteArray dat, int cnt);
    Confirms(QList<Confirm> cfs);
    Confirms();

    QString toQString() const;
    QByteArray toPureData() const;

private:
    QByteArray _dat;
    bool isValid = false;
    bool isEmpty = false;
    QString errorMessage;

    QList<Confirm> _cfs;
};

#endif
