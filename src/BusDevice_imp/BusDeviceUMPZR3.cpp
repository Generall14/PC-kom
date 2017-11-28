#include "BusDeviceUMPZR3.hpp"
#include "../Utils/StaticUtils.hpp"
#include <qDebug>

BusDeviceUMPZR3::BusDeviceUMPZR3(QString arg):
    BusDeviceUMP(arg)
{
    Desc::description = "BusDeviceUMPZR3";
}

void BusDeviceUMPZR3::OnRun()
{
    float step = ((float)TIME_STEP_MS)/1000.0;
    time += step;
    currentDoseRate = 201e-6+sin(time/(2.0*3.14))*100e-6;
    currentDose += (1e9/(1000.0*60.0*60.0))*currentDoseRate*(((float)TIME_STEP_MS));

    QMutexLocker locker(&mutex);
    for(int i=alist.size()-1;i>=0;i--)
    {
        alist[i].expireTimer -= step;
        if(alist[i].expireTimer<0)
        {
            alist.removeAt(i);
            continue;
        }
        alist[i].timer -= step;
        if(alist[i].timer<0)
        {
            alist[i].timer = alist[i].startTime;
            QByteArray toWrite;
            toWrite.append((char)0x00);
            toWrite.append((*this.*(alist[i].fptr))());
            emit AplWritePureData(toWrite);
        }
    }
}

QByteArray BusDeviceUMPZR3::OnDataRecieved(QByteArray data)
{
    QByteArray toWrite;
    uchar val = data.at(0);
    switch(val)
    {
    case (uchar)0x20:
        toWrite.append(DoseData());
        break;
    case (uchar)0x22:
        toWrite.append(DoseRateData());
        break;
    case (uchar)0x30:
        toWrite.append(StatusData());
        break;
    case (uchar)0x08:
        toWrite.append(AutoReportData(data));
        break;
    default:
        return toWrite;
    }
    return toWrite;
}

QByteArray BusDeviceUMPZR3::DoseData()
{
    QByteArray toWrite;
    toWrite.append(0xa0);
    toWrite.append(SU::float32to24(currentDoseRate));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::DoseRateData()
{
    QByteArray toWrite;
    toWrite.append(0xa2);
    toWrite.append((currentDose&0xFF0000000000)>>40);
    toWrite.append((currentDose&0x00FF00000000)>>32);
    toWrite.append((currentDose&0x0000FF000000)>>24);
    toWrite.append((currentDose&0x000000FF0000)>>16);
    toWrite.append((currentDose&0x00000000FF00)>>8);
    toWrite.append((currentDose&0x0000000000FF)>>0);
    return toWrite;
}

QByteArray BusDeviceUMPZR3::StatusData()
{
    QByteArray toWrite("Urzadzenie jest ok");
    toWrite.insert(0, 0xb0);
    toWrite.append((char)0x00);
    return toWrite;
}

QByteArray BusDeviceUMPZR3::AutoReportData(QByteArray dat)
{
    QByteArray toWrite;
    toWrite.append(0x88);

    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);

    QMutexLocker locker(&mutex);
    while(dat.size()>=3)
    {
        bool found = false;
        int nval = 0;
        nval |= (dat.at(1)<<8)&0xFF00;
        nval |= (dat.at(2)<<0)&0x00FF;
        for(int i=0;i<alist.size();i++)
        {
            if(alist.at(i).header==(uchar)dat.at(0))
            {
                found = true;
                alist[i].expireTimer = TIME_TO_EXPIRE_S;
                if(nval<0)
                    break;
                if(nval<alist[i].startTime)
                    alist[i].startTime = nval;
                alist[i].timer = alist[i].startTime;
                break;
            }
        }
        if(!found)
        {
            uchar val = dat.at(0);
            ars tars{nval, TIME_TO_EXPIRE_S, nval, val, NULL};
            switch(val)
            {
            case (uchar)0xa0:
                tars.fptr = &BusDeviceUMPZR3::DoseData;
                break;
            case (uchar)0xa2:
                tars.fptr = &BusDeviceUMPZR3::DoseRateData;
                break;
            default:
                break;
            }
            if(tars.fptr!=NULL)
                alist.append(tars);
        }
        dat.remove(0, 3);
    }

    return toWrite;
}
