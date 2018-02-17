#include "DataCollector.hpp"
#include "../../Frame_imp/FrameSG1.hpp"

DataCollector::DataCollector(int numberOfData, method typPomiaru, bool continuous):
    length(numberOfData),
    typ(typPomiaru),
    ciagly(continuous)
{
    timeres = FrameSG1::TimeRes();
}

DataCollector::~DataCollector()
{
}

void DataCollector::OnStop()
{
    emit Done();
}

void DataCollector::Run()
{
    QThread::msleep(1000);
    CalcData();
}

void DataCollector::RecievedFrame(QByteArray frame)
{
    QSharedPointer<Frame> tempf = QSharedPointer<Frame>(Factory::newFrame(frame));
    if(!tempf->isValid())
        return;

    int tempv = 0;
    tempv |= (frame.at(1)<<16)&0xFF0000;
    tempv |= (frame.at(2)<<8)&0x00FF00;
    tempv |= (frame.at(3)<<0)&0x0000FF;

    if(frame.at(0)=='C')
        dataList.push_back(tempv);
    else if(frame.at(0)=='Z')
        ADCList.push_back(tempv);
    else
        return;
}

void DataCollector::CalcData()
{
    int completed = 0;
    if(dataList.length()>1)
    {
        if(typ==metRap)
        {
            if(!ciagly)
            {
                if(dataList.length()>=length)
                    this->Stop();
            }
            while(dataList.length()>length)
                dataList.pop_front();
            completed = 1000*dataList.length()/length;
        }
        else
        {
            int sumac = 0;
            for(int datax: dataList)
                sumac += datax;
            if(!ciagly)
            {
                if(sumac>=length)
                    this->Stop();
            }
            while(sumac-dataList.at(0)>length)
            {
                dataList.pop_front();
                sumac = 0;
                for(int datax: dataList)
                    sumac += datax;
            }
            completed = 1000*sumac/length;
        }
    }

    while(ADCList.length()>dataList.length())
        ADCList.pop_front();

    int dataSum = 0;
    float dataMean = 0;
    if(!dataList.isEmpty())
    {
        for(int datax: dataList)
            dataSum += datax;
        dataMean = ((float)dataSum)/((float)dataList.length())/timeres;
    }

    int ADCSum = 0, ADCMean = 0;
    if(!ADCList.isEmpty())
    {
        for(int ADCx: ADCList)
            ADCSum += ADCx;
        ADCMean = ADCSum/ADCList.length();
    }

    emit SendStatus(dataMean, ADCMean, completed);
}
