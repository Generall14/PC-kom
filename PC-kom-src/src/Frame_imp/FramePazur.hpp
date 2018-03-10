#ifndef FRAMEPAZUR_HPP
#define FRAMEPAZUR_HPP

#include <QByteArray>
#include "../Frame.hpp"
#include "utils_Pazur/Confirms.hpp"
#include "utils_Pazur/Messages.hpp"

class FramePazur : public Frame
{
public:
    FramePazur(QByteArray ba);
    FramePazur(uchar from, uchar to, uchar id, bool fast, QList<Confirm> cfs=QList<Confirm>(), QList<Message> msgs=QList<Message>());
    ~FramePazur(){}

    virtual bool isValid();
    virtual QString toQString();
    virtual QString toShortQString();
    virtual QByteArray magicNumbers();

private:
    bool isHeaderOk();
    void parse();
    bool isItOk = false;

    QString dispHeader();

    uchar _from, _to, _id, _dataSize, _confs, _crc10add;
    bool _fast;

    Confirms _cfs;
    Messages _msgs;
};

#endif
