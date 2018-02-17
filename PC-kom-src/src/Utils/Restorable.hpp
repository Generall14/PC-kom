#ifndef RESTORABLE_HPP
#define RESTORABLE_HPP

#include <QString>
#include <QFile>
#include <QTextStream>

class Restorable
{
public:
    Restorable();
protected:
    bool Store(QString fileName, QString textValue);
    bool Restore(QString fileName, QString& textValue);
private:
    QFile _file;
    QTextStream _textStream;
};

#endif
