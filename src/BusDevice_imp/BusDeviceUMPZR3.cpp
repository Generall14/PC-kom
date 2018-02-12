#include "BusDeviceUMPZR3.hpp"
#include "../Utils/StaticUtils.hpp"
//#include <qDebug>

BusDeviceUMPZR3::BusDeviceUMPZR3(QString arg):
    BusDeviceUMP(arg)
{
    Desc::description = "BusDeviceUMPZR3";
}

void BusDeviceUMPZR3::OnRun()
{
    float step = ((float)TIME_STEP_MS)/1000.0;
    time += step;
//    currentDoseRate = 201e-6+sin(time/(2.0*3.14))*100e-6;
    currentDose += (1e9/(1000.0*60.0*60.0))*currentDoseRate*(((float)TIME_STEP_MS));
    if(currentDose>doseAlarm)
        doseAlarmState = true;
    else
        doseAlarmState = false;

    if(currentDoseRate>(doseRateAlarm+doseRateAlarmHist))
    {
        if(!latchModeAlarm)
            doseRateAlarmState = true;
        else
        {
            if(doseRateAlarmStateReseted)
            {
                doseRateAlarmState = true;
                doseRateAlarmStateReseted = false;
            }
        }
    }
    else if(currentDoseRate<doseRateAlarm)
    {
        if(!latchModeAlarm)
            doseRateAlarmState = false;
        else
        {
            doseRateAlarmStateReseted = true;
        }
    }


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
        toWrite.append(DoseRateData());
        break;
    case (uchar)0x21:
        toWrite.append(EstData());
        break;
    case (uchar)0x22:
        toWrite.append(DoseData());
        break;
    case (uchar)0x23:
        toWrite.append(SetDoseData(data));
        break;
    case (uchar)0x24:
        toWrite.append(DoseAlarmStateData());
        break;
    case (uchar)0x25:
        toWrite.append(SetDoseAlarmLevelData(data));
        break;
    case (uchar)0x26:
        toWrite.append(GetDoseAlarmLevelData());
        break;
    case (uchar)0x29:
        toWrite.append(DoseRateAlarmStateData());
        break;
    case (uchar)0x2A:
        toWrite.append(SetDoseRateAlarmLevelData(data));
        break;
    case (uchar)0x2B:
        toWrite.append(GetDoseRateAlarmLevelData());
        break;
    case (uchar)0x2C:
        toWrite.append(SetDoseRateAlarmModeData(data));
        break;
    case (uchar)0x2D:
        toWrite.append(GetDoseRateAlarmModeData());
        break;
    case (uchar)0x2E:
        toWrite.append(SetDoseRateAlarmHisteresisData(data));
        break;
    case (uchar)0x2F:
        toWrite.append(GetDoseRateAlarmHisteresisData());
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
    toWrite.append(0xa2);
    toWrite.append(SU::int48ToByteArray(currentDose));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::DoseAlarmStateData()
{
    QByteArray temp;
    temp.append(0xa4);
    if(doseAlarmState)
        temp.append((char)0xFF);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray BusDeviceUMPZR3::DoseRateAlarmStateData()
{
    QByteArray temp;
    temp.append(0xa9);
    if(doseRateAlarmState)
        temp.append((char)0xFF);
    else
        temp.append((char)0x00);
    return temp;
}

QByteArray BusDeviceUMPZR3::GetDoseAlarmLevelData()
{
    QByteArray toWrite;
    toWrite.append(0xa6);
    toWrite.append(SU::int48ToByteArray(doseAlarm));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::GetDoseRateAlarmLevelData()
{
    QByteArray toWrite;
    toWrite.append(0xab);
    toWrite.append(SU::float32to24(doseRateAlarm));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::GetDoseRateAlarmHisteresisData()
{
    QByteArray toWrite;
    toWrite.append(0xaf);
    toWrite.append(SU::float32to24(doseRateAlarmHist));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::SetDoseData(QByteArray dat)
{
    QByteArray toWrite;
    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);

    long long temp = SU::byteArray2Int48(dat);
    if(temp>=0)
    {
        currentDose = temp;
        toWrite.append(0xA3);
    }

    return toWrite;
}

QByteArray BusDeviceUMPZR3::SetDoseAlarmLevelData(QByteArray dat)
{
    QByteArray toWrite;
    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);

    long long temp = SU::byteArray2Int48(dat);
    if(temp>=0)
    {
        doseAlarm = temp;
        toWrite.append(0xA5);
    }

    return toWrite;
}

QByteArray BusDeviceUMPZR3::SetDoseRateAlarmLevelData(QByteArray dat)
{
    QByteArray toWrite;
    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);

    float temp = SU::float24to32(dat);
    if(temp>=0)
    {
        doseRateAlarm = temp;
        toWrite.append(0xAA);
    }

    return toWrite;
}

QByteArray BusDeviceUMPZR3::SetDoseRateAlarmHisteresisData(QByteArray dat)
{
    QByteArray toWrite;
    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);

    float temp = SU::float24to32(dat);
    if(temp>=0)
    {
        doseRateAlarmHist = temp;
        toWrite.append(0xAE);
    }

    return toWrite;
}

QByteArray BusDeviceUMPZR3::SetDoseRateAlarmModeData(QByteArray dat)
{
    QByteArray toWrite;
    if(dat.isEmpty())
        return toWrite;
    dat.remove(0, 1);
    toWrite.append(0xAC);
    latchModeAlarm = SU::byteArray2bool(dat);
    return toWrite;
}

QByteArray BusDeviceUMPZR3::GetDoseRateAlarmModeData()
{
    QByteArray toWrite;
    toWrite.append(0xad);
    toWrite.append(SU::boolToByteArray(latchModeAlarm));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::DoseRateData()
{
    QByteArray toWrite;
    toWrite.append(0xa0);
    toWrite.append(SU::float32to24(currentDoseRate));
    return toWrite;
}

QByteArray BusDeviceUMPZR3::StatusData()
{
    QByteArray toWrite("Urzadzenie jest ok");
    toWrite.insert(0, 0xb0);
    toWrite.append((char)0x00);
    return toWrite;
}

QByteArray BusDeviceUMPZR3::EstData()
{
    int c = qrand()%0xFFFF;
    float n = (float)(qrand()%101)/100.0;
    QByteArray toWrite;
    toWrite.append(0xA1);
    toWrite.append(SU::float32to24(n));
    toWrite.append(SU::int32ToByteArray(c));
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
                tars.fptr = &BusDeviceUMPZR3::DoseRateData;
                break;
            case (uchar)0xa1:
                tars.fptr = &BusDeviceUMPZR3::EstData;
                break;
            case (uchar)0xa2:
                tars.fptr = &BusDeviceUMPZR3::DoseData;
                break;
            case (uchar)0xa4:
                tars.fptr = &BusDeviceUMPZR3::DoseAlarmStateData;
                break;
            case (uchar)0xa9:
                tars.fptr = &BusDeviceUMPZR3::DoseRateAlarmStateData;
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
