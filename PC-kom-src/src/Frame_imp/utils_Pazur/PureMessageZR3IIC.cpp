#include "PureMessageZR3IIC.hpp"
#include <cassert>
#include <QDebug>
#include "src/Utils/StaticUtils.hpp"
#include "Quantile.hpp"

QString getWho(char b, QString temp)
{
    temp += "[ ";
    if(b&(0x01<<0))
        temp += "Tg1 ";
    if(b&(0x01<<1))
        temp += "Tg2 ";
    if(b&(0x01<<2))
        temp += "Tg3 ";
    if(b&(0x01<<3))
        temp += "Tg8 ";
    if(b&(0x01<<4))
        temp += "fTg1 ";
    if(b&(0x01<<5))
        temp += "fTg2 ";
    if(b&(0x01<<6))
        temp += "Tgx ";
    temp += "]";
    //if(b)
        qDebug() << temp;
    return temp;
}

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
//        if(cmd.size()<5)
//            break;
        uint totalImp = 0, cntImp = 0;
        totalImp |= cmd.at(5)&0xFF;
        totalImp |= (cmd.at(6)<<8)&0xFF00;
        totalImp |= (cmd.at(7)<<16)&0xFF0000;
        totalImp |= (cmd.at(8)<<24)&0xFF000000;
        cntImp |= cmd.at(9)&0xFF;
        cntImp |= (cmd.at(10)<<8)&0xFF00;
        float timp = (float)totalImp/(float)cntImp*125e-9;
        temp += "imp: "+SU::displayFloat(timp, 2, 'f')+"s ("+QString::number(cntImp)+"), ";
        uint64_t ftg2=0;
        ftg2 |= cmd.at(11)&0xFF;
        ftg2 |= (cmd.at(12)<<8)&0xFF00;
        ftg2 |= (cmd.at(13)<<16)&0xFF0000;
        ftg2 |= (cmd.at(14)<<24)&0xFF000000;
        ftg2 |= (cmd.at(15)<<32)&0xFF00000000;
        ftg2 |= (cmd.at(16)<<40)&0xFF0000000000;
        temp += "fTg2: "+SU::displayFloat(float(ftg2)/128.0/8*125e-9, 2, 'f')+"s, ";
        uint64_t MSM_sTG = 0, MSM_nTG = 0;
        MSM_sTG |= cmd.at(17)&0xFF;
        MSM_sTG |= (cmd.at(18)<<8)&0xFF00;
        MSM_sTG |= (cmd.at(19)<<16)&0xFF0000;
        MSM_sTG |= (cmd.at(20)<<24)&0xFF000000;
        MSM_sTG |= (cmd.at(21)<<32)&0xFF00000000;
        MSM_sTG |= (cmd.at(22)<<40)&0xFF0000000000;
        MSM_nTG |= cmd.at(23)&0xFF;
        MSM_nTG |= (cmd.at(24)<<8)&0xFF00;
        MSM_nTG |= (cmd.at(25)<<16)&0xFF0000;
        MSM_nTG |= (cmd.at(26)<<24)&0xFF000000;
        temp += getWho(cmd.at(27), " Rise");
        temp += getWho(cmd.at(28), " Fall");
        float thole = (float)MSM_sTG/(float)MSM_nTG*125e-9;
        temp += "hole: "+SU::displayFloat(thole, 2, 'f')+"s ("+QString::number(MSM_nTG)+"), ";
        temp += QString("hist|||");
        for(int u=0;u<5;++u)
        {
            temp += QString(" %1 |").arg(cmd.at(0)&0xFF);
            cmd = cmd.mid(1);
        }
        temp += "||";
        found = true;
        break;
    }
    case 0x04:
    {
        float wpri = SU::byteArray322Float32(cmd.mid(0, 4));
        float wsec = SU::byteArray322Float32(cmd.mid(4, 4));
        float rng = SU::byteArray322Float32(cmd.mid(10, 4));
        uint chng = 0, nr = 0;
        nr |= cmd.at(8)&0xFF;
        nr |= (cmd.at(9)<<8)&0xFF00;
        chng |= cmd.at(14)&0xFF;
        chng |= (cmd.at(15)<<8)&0xFF00;

        temp += "Wpri: "+Quantile::makeStringB(wpri, nr, "Sv");
        temp += ", Wsec: "+Quantile::makeStringB(wsec, nr, "Sv");
        temp += ", Nr: "+QString::number(nr);
        temp += ", Rng: "+SU::displayFloat(rng, 2, 'f');
        temp += ", Chng: "+QString::number(chng);
        temp += ","+getWho(cmd.at(16), " Rise")+getWho(cmd.at(17), " Fall");

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
