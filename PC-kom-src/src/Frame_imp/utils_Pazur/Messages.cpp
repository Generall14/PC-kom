#include "Messages.hpp"
#include <QDebug>

Messages::Messages(QByteArray dat, int siz, char addcrc):
    _dat(dat),
    _addcrc(addcrc)
{
    qDebug() << dat;
    qDebug() << siz;
    if(dat.isEmpty())
    {
        isEmpty = true;
        return;
    }
    if(dat.size()!=siz)
    {
        isValid = false;
        errorMessage = " Invalid data length";
        return;
    }
    // crc
    while(dat.size()>0)
    {
        if(dat.size()<3)
        {
            _msgs.push_back(Message(dat));
            break;
        }
        char s = dat.at(1)&0x3F;
        if(dat.size()<s+2)
        {
            _msgs.push_back(Message(dat));
            break;
        }
        _msgs.push_back(Message(dat.mid(0, s+2)));
        dat.remove(0, s+2);
    }
    isValid = true;
}

Messages::Messages(QList<Message> msgs):
    _msgs(msgs)
{
    if(msgs.isEmpty())
        isEmpty = true;
    isValid = true;

    for(auto a: msgs)
        _dat.append(a.toPureData());
    _dat.append(0xFF);//crc...
}

Messages::Messages()
{
}

QString Messages::toQString() const
{
    if(!isEmpty)
    {
        QString temp = "\r\n[Messages: ";
        if(!isValid)
        {
            temp.append(errorMessage + "\r\n");
            for(auto ch: _dat)
                temp.append(QString("0x%1 ").arg(ch, 2, 16, QChar('0')));
        }
        else
        {
            for(auto a: _msgs)
                temp.push_back("\r\n\t( "+a.toQString()+" )");
        }
        temp.append("\r\n]");
        return temp;
    }
    else
        return "";
}

QByteArray Messages::toPureData() const
{
    return _dat;
}

char Messages::addCrc10() const
{
    return _addcrc;
}
