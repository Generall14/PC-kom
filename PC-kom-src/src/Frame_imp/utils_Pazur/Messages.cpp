#include "Messages.hpp"
#include <QDebug>
#include "Utils/CRC.hpp"

Messages::Messages(QByteArray dat, int siz, char addcrc, char id):
    _dat(dat),
    _addcrc(addcrc)
{
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
    uint16_t crc = CRC::crc10(dat.mid(0, dat.size()-1), 0x155^id);
    uchar crch = (crc>>8)&0x03;
    uchar crcl = crc&0xFF;
    if((crcl!=(uchar)dat.at(dat.size()-1))||(crch!=(uchar)addcrc))
    {
        isValid = false;
        errorMessage = " Invalid crc";
        return;
    }
    while(dat.size()>0)
    {
        if(dat.size()==1)
            break;
        if(dat.size()<2)
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

Messages::Messages(QList<Message> msgs, uchar id):
    _msgs(msgs)
{
    _dat.clear();
    isValid = true;
    if(msgs.isEmpty())
    {
        isEmpty = true;
        return;
    }

    for(auto a: msgs)
        _dat.append(a.toPureData());
    uint16_t crc = CRC::crc10(_dat, 0x155^id);

    _addcrc = (crc>>8)&0x03;
    uchar crcl = crc&0xFF;
    _dat.append(crcl);
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
                temp.append(QString("0x%1 ").arg((uint)ch&0xFF, 2, 16, QChar('0')));
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
