#ifndef CONFIRM_HPP
#define CONFIRM_HPP

#include <QChar>
#include <QString>

class Confirm
{
public:
    Confirm(char dat);
    Confirm(char adr, char id);

    QString toQString() const;
    char toPureData() const;

    void get(char &adr, char &id) const;

private:
    char _id, _adr;
    char _dat;
};

#endif
