#include "PureMessageZR3IIC.hpp"
#include <cassert>
#include <QDebug>
#include "src/Utils/StaticUtils.hpp"
#include "Quantile.hpp"

QString PureMessageZR3IIC::getWho(char b, QString temp)
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
    if(b)
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
    uchar code = uchar(_arr.at(1));
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
    case slavePALSY_c:
    {
        if(cmd.size()!=0)
            break;
        temp = "slavePALSY";
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
    case masterRET_c:
    {
        if(cmd.size()<10)
            break;
        uint16_t val = 0;
        val = cmd.at(0)&0xFF;
        val |= (cmd.at(1)<<8)&0xFF00;
        temp = QString("slaveRET, R12: 0x%1, ").arg(val&0xFFFF, 4, 16, QChar('0'));
        val = cmd.at(2)&0xFF;
        val |= (cmd.at(3)<<8)&0xFF00;
        temp += QString("R13: 0x%1, ").arg(val&0xFFFF, 4, 16, QChar('0'));
        val = cmd.at(4)&0xFF;
        val |= (cmd.at(5)<<8)&0xFF00;
        temp += QString("R14: 0x%1, ").arg(val&0xFFFF, 4, 16, QChar('0'));
        val = cmd.at(6)&0xFF;
        val |= (cmd.at(7)<<8)&0xFF00;
        temp += QString("R15: 0x%1, ").arg(val&0xFFFF, 4, 16, QChar('0'));
        val = cmd.at(8)&0xFF;
        val |= (cmd.at(9)<<8)&0xFF00;
        temp += QString("SR: 0x%1").arg(val&0xFFFF, 4, 16, QChar('0'));
        found = true;
        break;
    }
    case masterDBG_c:
    {
        if(cmd.size()<27)
            break;
        uint totalImp = 0, cntImp = 0;
        totalImp |= cmd.at(5)&0xFF;
        totalImp |= (cmd.at(6)<<8)&0xFF00;
        totalImp |= (cmd.at(7)<<16)&0xFF0000;
        totalImp |= (uint64_t(cmd.at(8))<<24)&0xFF000000;
        cntImp |= cmd.at(9)&0xFF;
        cntImp |= (cmd.at(10)<<8)&0xFF00;
        float timp = float(totalImp)/float(cntImp)*float(125e-9);
        temp += "imp: "+SU::displayFloat(timp, 2, 'f')+"s ("+QString::number(cntImp)+"), ";
        uint64_t ftg2=0;
        ftg2 |= cmd.at(11)&0xFF;
        ftg2 |= (cmd.at(12)<<8)&0xFF00;
        ftg2 |= (cmd.at(13)<<16)&0xFF0000;
        ftg2 |= (uint64_t(cmd.at(14))<<24)&0xFF000000;
        ftg2 |= (uint64_t(cmd.at(15))<<32)&0xFF00000000;
        ftg2 |= (uint64_t(cmd.at(16))<<40)&0xFF0000000000;
        temp += "fTg2: "+SU::displayFloat(ftg2*125e-9/128.0, 2, 'f')+"s, ";
        uint64_t MSM_sTG = 0, MSM_nTG = 0;
        MSM_sTG |= cmd.at(17)&0xFF;
        MSM_sTG |= (cmd.at(18)<<8)&0xFF00;
        MSM_sTG |= (cmd.at(19)<<16)&0xFF0000;
        MSM_sTG |= (uint64_t(cmd.at(20))<<24)&0xFF000000;
        MSM_sTG |= (uint64_t(cmd.at(21))<<32)&0xFF00000000;
        MSM_sTG |= (uint64_t(cmd.at(22))<<40)&0xFF0000000000;
        MSM_nTG |= cmd.at(23)&0xFF;
        MSM_nTG |= (cmd.at(24)<<8)&0xFF00;
        MSM_nTG |= (cmd.at(25)<<16)&0xFF0000;
        MSM_nTG |= (uint64_t(cmd.at(26))<<24)&0xFF000000;
        float thole = float(MSM_sTG)/float(MSM_nTG)*float(125e-9);
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
    case masterMES:
    {
        if(cmd.size()<20)
            break;
        float wpri = SU::byteArray322Float32(cmd.mid(0, 4));
        float wsec = SU::byteArray322Float32(cmd.mid(4, 4));
        float rng = SU::byteArray322Float32(cmd.mid(8, 4));
        float ene = SU::byteArray322Float32(cmd.mid(12, 4))*1000;
        uint chng = 0, nr = 0;
        nr |= cmd.at(16)&0xFF;
        nr |= (cmd.at(17)<<8)&0xFF00;
        chng |= cmd.at(18)&0xFF;
        chng |= (cmd.at(19)<<8)&0xFF00;

        temp += "Energy: "+SU::displayFloat(ene, 2, 'f')+"eV";
        temp += ", Wpri: "+Quantile::makeStringB(wpri, nr, "Sv");
        temp += ", Wsec: "+Quantile::makeStringB(wsec, nr, "Sv");
        temp += ", Nr: "+QString::number(nr);
        temp += ", Rng: "+SU::displayFloat(rng, 2, 'f');
        temp += ", Chng: "+QString::number(chng);

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
    dat.insert(0, char(dat.size()));
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
    temp.append(char(slaveRST_c));
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveCALL()
{
    QByteArray temp;
    temp.append(slaveCALL_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slavePALSY()
{
    QByteArray temp;
    temp.append(slavePALSY_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveGET_DBG_DAT()
{
    QByteArray temp;
    temp.append(slaveGET_DBG_DAT_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveRST_HIST()
{
    QByteArray temp;
    temp.append(slaveRST_HIST_c);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveMES_RST(uint16_t D)
{
    QByteArray temp;
    temp.append(slaveMES_RST_c);
    temp.append(D&0xFF);
    temp.append((D>>8)&0xFF);
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveRDSECTION(uint nr)
{
    QByteArray temp;
    temp.append(slaveRDSECTION_c);
    temp.append(char(nr));
    return appendSize(temp);
}

QByteArray PureMessageZR3IIC::slaveWRSECTION(uint nr, const QByteArray& data)
{
    QByteArray temp;
    temp.append(slaveWRSECTION_c);
    temp.append(char(nr));
    temp.append(data);
    return appendSize(temp);
}
