#include "ZR3UIFrame.hpp"
#include <QInputDialog>
#include <QDebug>
#include "../../Frame_imp/FrameZR3.hpp"
#include "../../Factory.hpp"

ZR3UIFrame::ZR3UIFrame(QFrame* parent, uchar adr):
    QObject(parent),
    cFrame(parent),
    _adr(adr)
{
    ui = new ZR3UIFrameUI(this);
}

ZR3UIFrame::~ZR3UIFrame()
{
    delete ui;
}

void ZR3UIFrame::Init()
{
    ui->Init();
}

void ZR3UIFrame::protSET_ADR()
{
    QString astring = QString::number(_adr, 16);
    while(astring.length()<2)
        astring.insert(0, '0');

    bool ok;
    QString text = QInputDialog::getText(cFrame, "Podaj adres", "Adres:", QLineEdit::Normal, astring, &ok);

    if(!ok)
        return;

    text = text.left(2);
    char nadr = text.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+text+"\".");
        return;
    }

    QByteArray temp;
    temp.append(0xFF);
    temp.append(0x02);
    temp.append(_adr);
    temp.append(_myAdr);
    temp.append((char)0x01);
    temp.append(nadr);
    FrameZR3::AppendLRC(temp);
    emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(temp)));
    emit AdresChanged(nadr);
    _adr = nadr;
}

void ZR3UIFrame::protSET_NEXT_ADR()
{
    bool ok;
    QString text = QInputDialog::getText(cFrame, "Podaj adres", "Adres:", QLineEdit::Normal, "FE", &ok);

    if(!ok)
        return;

    text = text.left(2);
    char nadr = text.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+text+"\".");
        return;
    }

    QByteArray temp;
    temp.append(0xFF);
    temp.append(0x03);
    temp.append(_adr);
    temp.append(_myAdr);
    temp.append((char)0x01);
    temp.append(nadr);
    FrameZR3::AppendLRC(temp);
    emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(temp)));
}

void ZR3UIFrame::protHELLO()
{
    QByteArray temp;
    temp.append(0xFF);
    temp.append(0x01);
    temp.append(_adr);
    temp.append(_myAdr);
    temp.append((char)0x00);
    FrameZR3::AppendLRC(temp);
    emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(temp)));
}

void ZR3UIFrame::aplReadReq(QString type, int offset, char size)
{
    QByteArray temp;
    temp.append(_adr);
    if(!type.compare("aplStringListDescriptor"))
        temp.append(QChar(0x0A));

    temp.append((offset>>8)&0xFF);
    temp.append((offset>>0)&0xFF);
    temp.append((size>>0)&0xFF);
    emit PureDataToMedium(temp);
}

void ZR3UIFrame::InitZR3ReadFile(uchar header)
{
    if(rfile!=NULL)
        return;
    rfile = new ZR3ReadFile(header);
    connect(rfile, &ZR3ReadFile::SendDataFrame, [=](QByteArray ba){ba.insert(0, _adr);emit PureDataToMedium(ba);});
    connect(rfile, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(rfile, SIGNAL(Done(uchar,QByteArray)), this, SLOT(FinalizeZR3ReadFile(uchar,QByteArray)));
    connect(this, SIGNAL(InternalDataReaded(QByteArray)), rfile, SLOT(RecievedData(QByteArray)), Qt::QueuedConnection);
    rfile->start(QThread::NormalPriority);
}

void ZR3UIFrame::FinalizeZR3ReadFile(uchar _header, QByteArray arr)
{
    rfile = NULL;
    if(arr.isEmpty())
        return;
    if(_header==0x0A)
    {
        strings = arr;
        ParseStrings();
    }
    else if(_header==0x01)
    {
        devDescriptor = arr;
        ParseDevice();
    }
}

void ZR3UIFrame::ParseStrings()
{
    stringi.clear();
    QList<uint16_t> ptrs;
    int lasti = -3;
    while(1)
    {
        if((strings.at(lasti+3)==QChar(0x00)))
            break;
        int ti = strings.indexOf(char(0x00), lasti+3);
        if(ti<=0)
            break;
        stringi.push_back(QStringList());
        stringi[stringi.size()-1].push_back(QString(strings.mid(lasti+3, ti-lasti+3)));
        uint16_t tt = 0;
        tt = (strings.at(ti+1)<<8)&0xFF00;
        tt |= strings.at(ti+2)&0xFF;
        ptrs.push_back(tt);
        lasti = ti;
    }
    for(int i=0;i<ptrs.size();++i)
    {
        if(i+1==ptrs.size())
        {
            for(QByteArray la: strings.mid(ptrs.at(i)).split(0x00))
            {
                if(!la.isEmpty())
                    stringi[i].append(QString(la));
            }
        }
        else
        {
            for(QByteArray la: strings.mid(ptrs.at(i), ptrs.at(i+1)-ptrs.at(i)).split(0x00))
            {
                if(!la.isEmpty())
                    stringi[i].append(QString(la));
            }
        }
    }

    ui->UpdateStringsTable(stringi);
}

void ZR3UIFrame::ParseDevice()
{
    if(devDescriptor.isEmpty())
        return;

    parsedDevDesc.clear();
    devClasses.clear();

    QByteArray temp = devDescriptor;
    if(temp.size()<3)
    {
        emit Error("Błąd parsowania deskryptora urządzenia: devDescriptor.size()<3");
        return;
    }
    for(int i=0;i<3;++i)
        parsedDevDesc.append(QString::number((int)temp.at(i)));

    temp.remove(0, 3);
    QList<int> zeros;
    for(int i=0;i<temp.size();++i)
        if(temp.at(i)==0x00)
            zeros.append(i);
    if(zeros.size()<3)
    {
        emit Error("Błąd parsowania deskryptora urządzenia: błąd tekstów opisowych");
        return;
    }
    parsedDevDesc.append(QString(temp.mid(0, zeros.at(0))));
    parsedDevDesc.append(QString(temp.mid(zeros.at(0)+1, zeros.at(1)-zeros.at(0))));
    parsedDevDesc.append(QString(temp.mid(zeros.at(1)+1, zeros.at(2)-zeros.at(1))));
    temp.remove(0, zeros.at(2)+1);

    zeros.clear();
    for(int i=0;i<temp.size();++i)
        if((temp.at(i)==(char)0xFF))
            zeros.append(i);
    if(zeros.size()<2)
    {
        emit Error("Błąd parsowania deskryptora urządzenia: błąd wskaźników tekstowych");
        return;
    }
    QList<int> ptrs;
    for(int i=0;i<zeros.at(0);++i)
        ptrs.append(temp.at(i));
    parsedDevDesc.append(ConcStringPointers(ptrs, currentLang));
    ptrs.clear();
    for(int i=zeros.at(0)+1;i<zeros.at(1);++i)
        ptrs.append(temp.at(i));
    parsedDevDesc.append(ConcStringPointers(ptrs, currentLang));
    temp.remove(0, zeros.at(1)+1);

    while(!temp.isEmpty())
    {
        ptrs.clear();
        zeros.clear();
        QString tclass;
        for(int i=0;i<temp.size();++i)
        {
            if(temp.at(i)==0x00)
            {
                zeros.append(i);
                if(zeros.size()>=2)
                    break;
            }
        }
        if(zeros.size()<2)
        {
            emit Error("Błąd parsowania listy funkcjonalności");
            return;
        }
        tclass = QString(temp.mid(0, zeros.at(0)));
        for(int i=zeros.at(0)+1;i<zeros.at(1);++i)
            ptrs.append(temp.at(i));
        davClass tdv{tclass, ptrs};
        devClasses.append(tdv);
        if(zeros.at(1)<temp.size())
            temp.remove(0, zeros.at(1)+1);
        else
        {
            emit Error("Błąd parsowania listy funkcjonalności");
            return;
        }
    }

    ui->UpdateDevDescriptor(parsedDevDesc, devClasses);
}

QString ZR3UIFrame::ConcStringPointers(QList<int> ptrs, int lang)
{
    if(lang>=stringi.size())
    {
        {
            emit Error("Błąd konkatenacji listy stringów: nieprawidłowy numer języka: " + QString::number(lang));
            return "lang err";
        }
    }
    QStringList tempList = stringi.at(lang);
    QString temp;
    for(int i: ptrs)
    {
        i += 1;
        if(i>=tempList.size())
        {
            emit Error("Błąd konkatenacji listy stringów: nieprawidłowy wskaźnik tekstu: " + QString::number(i));
            return temp + " ???";
        }
        temp.append(" " + tempList.at(i));
    }
    if(temp.size()>0)
        temp.remove(0, 1);//usuwanie spacji na początku
    return temp;
}

void ZR3UIFrame::FrameToUI(QSharedPointer<Frame> frame)
{
    emit InternalDataReaded(frame->pureData().mid(5, frame->pureData().at(4)));
}

uchar ZR3UIFrame::Adr() const
{
    return _adr;
}

void ZR3UIFrame::UpdateCurrentLanguage(int newLang)
{
    currentLang = newLang;
    if(!stringi.isEmpty())
    {
        ParseDevice();
    }
}
