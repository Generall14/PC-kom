#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <QChar>
#include <QString>

class Message
{
public:
    Message(QByteArray arr);
    Message(char adr, char ifs, QByteArray dat, char x=0x00);

    QString toQString() const;
    QByteArray toPureData() const;

    void get(char &adr, char &ifs, QByteArray &dat, char &x) const;

private:
    char _adr, _ifs, _size, _x;
    QByteArray _dat;
    bool _isValid;
};

#endif
