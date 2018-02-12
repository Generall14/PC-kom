#ifndef METHOD_HPP
#define METHOD_HPP

#include <QString>
#include <QList>
#include <QByteArray>
#include "param.hpp"

struct method
{
    char header;
    bool direct;
    bool isResponse;
    bool autoReport;
    int timeout;
    char secondHeader;
    QString tooltip;
    QString desc;
    QList<param> params;
    QByteArray data; // przesyłane dane (tylko przy wykonywaniu transakcji)
};

#endif
