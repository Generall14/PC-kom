#include "PureMessageZR3IIC.hpp"
#include <cassert>
#include <QDebug>
#include "src/Utils/StaticUtils.hpp"

QString PureMessageZR3IIC::desc(QByteArray _arr)
{
    QString temp;

    if(_arr.size()<2)
        return temp;

    if(_arr.at(0)!=(_arr.size()-1))
    {
        temp = "Invalid iic data: ";
        for(auto ch: _arr)
            temp.append(QString("0x%1 ").arg(ch&0xFF, 2, 16, QChar('0')));
        return temp;
    }

    bool found = false;
    uchar code = _arr.at(1);
    QByteArray cmd;
    if(_arr.size()>2)
        cmd = _arr.mid(2);
    switch(code)
    {
    case masterTEST_c:
    {
        if(cmd.size()!=0)
            break;
        temp = "masterTEST";
        found = true;
        break;
    }
    case slaveTEST_c:
    {
        if(cmd.size()!=0)
            break;
        temp = "slaveTEST";
        found = true;
        break;
    }
    case slaveRDSECTION_c:
    {
        if(cmd.size()!=1)
            break;
        temp = QString("slaveRDSECTION, nr 0x%1").arg(cmd.at(0)&0xFF, 2, 16, QChar('0'));
        found = true;
        break;
    }
    case masterRDSECTIONo_c:
    {
        if(cmd.size()<1)
            break;
        temp = QString("masterRDSECTIONo, nr 0x%1, data: ").arg(cmd.at(0)&0xFF, 2, 16, QChar('0'));
        for(auto ch: cmd.mid(1))
            temp.append(QString("0x%1 ").arg(ch&0xFF, 2, 16, QChar('0')));
        found = true;
        break;
    }
    case slaveWRSECTION_c:
    {
        if(cmd.size()<1)
            break;
        temp = QString("slaveWRSECTION, nr 0x%1, data: ").arg(cmd.at(0)&0xFF, 2, 16, QChar('0'));
        for(auto ch: cmd.mid(1))
            temp.append(QString("0x%1 ").arg(ch&0xFF, 2, 16, QChar('0')));
        found = true;
        break;
    }
    case 0x03:
    {
        if(cmd.size()<6)
            break;
        uint total = 0, cnt = 0;
        total |= cmd.at(0)&0xFF;
        total |= (cmd.at(1)<<8)&0xFF00;
        total |= (cmd.at(2)<<16)&0xFF0000;
        total |= (cmd.at(3)<<24)&0xFF000000;
        cnt |= cmd.at(4)&0xFF;
        cnt |= (cmd.at(5)<<8)&0xFF00;
        float freq = (float)cnt/(float)total/125e-9/2;
        temp = QString("MES = %1 Hz, cnt %2, thole: %3").arg(freq).arg(cnt).arg(total);
        found = true;
        break;
    }
    default:
        break;
    }

    if(!found)
    {
        temp = "Unknown iic data: ";
        for(auto ch: _arr)
            temp.append(QString("0x%1 ").arg(ch&0xFF, 2, 16, QChar('0')));
    }

    return temp;
}

QByteArray PureMessageZR3IIC::appendSize(QByteArray dat)
{
    dat.insert(0, dat.size());
    return dat;
}

QByteArray PureMessageZR3IIC::slaveTEST()
{
    QByteArray temp;
    temp.append(slaveTEST_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveRST()
{
    QByteArray temp;
    temp.append(slaveRST_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveRDSECTION(uint nr)
{
    QByteArray temp;
    temp.append(slaveRDSECTION_c);
    temp.append(nr);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveWRSECTION(uint nr, QByteArray data)
{
    QByteArray temp;
    temp.append(slaveWRSECTION_c);
    temp.append(nr);
    temp.append(data);
    return appendSize(temp);
}
