#include "ZR3UIFrame.hpp"
#include <QInputDialog>
#include <QDebug>
#include "../../Frame_imp/FrameZR3.hpp"
#include "../../Factory.hpp"
#include "param.hpp"

ZR3UIFrame::ZR3UIFrame(QFrame* parent, uchar adr):
    QObject(parent),
    cFrame(parent),
    _adr(adr)
{
    ui = new ZR3UIFrameUI(this);

    tMaker = NULL;
    tMaker = new TransactionMaker();
    connect(tMaker, &TransactionMaker::SendDataFrame, [=](QByteArray ba){ba.insert(0, _adr);emit PureDataToMedium(ba);});
    connect(tMaker, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(this, SIGNAL(HALT()), tMaker, SLOT(Stop()));
    connect(this, SIGNAL(InternalDataReaded(QByteArray)), tMaker, SLOT(RecievedData(QByteArray)), Qt::QueuedConnection);
    tMaker->start(QThread::NormalPriority);
}

ZR3UIFrame::~ZR3UIFrame()
{
    emit HALT();
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
    rfile = new ZR3ReadFile(header);
    connect(rfile, &ZR3ReadFile::SendDataFrame, [=](QByteArray ba){ba.insert(0, _adr);emit PureDataToMedium(ba);});
    connect(rfile, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(rfile, SIGNAL(Done(uchar,QByteArray)), this, SLOT(FinalizeZR3ReadFile(uchar,QByteArray)));
    connect(this, SIGNAL(InternalDataReaded(QByteArray)), rfile, SLOT(RecievedData(QByteArray)), Qt::QueuedConnection);
    rfile->start(QThread::NormalPriority);
}

void ZR3UIFrame::FinalizeZR3ReadFile(uchar _header, QByteArray arr)
{
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
    else if(_header==0x09)
    {
        methDescriptor = arr;
        ParseMethods();
    }
}

/**
 * Funkcja przetwarza dane binarne strings na listę stringów stringi.
 */
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
    ParseDevice();
    ParseMethods();
}

/**
 * Funkcja przetwarza dane binarne devDescriptor na opis urządzenia parsedDevDesc.
 */
void ZR3UIFrame::ParseDevice()
{
    if(stringi.isEmpty())
        return;
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

    try
    {
        parsedDevDesc.append(ReadAndRemoveNextSimpleString(temp));
        parsedDevDesc.append(ReadAndRemoveNextSimpleString(temp));
        parsedDevDesc.append(ReadAndRemoveNextSimpleString(temp));
        parsedDevDesc.append(ReadAndRemoveNextString(temp));
        parsedDevDesc.append(ReadAndRemoveNextString(temp));
    }
    catch(QString exc)
    {
        emit Error(exc);
        return;
    }

    while(!temp.isEmpty())
    {
        QString tclass;
        try
        {
            tclass = ReadAndRemoveNextSimpleString(temp);
        }
        catch(QString exc)
        {
            emit Error(exc);
            return;
        }

        int x00 = -1;
        for(int i=0;i<temp.size();++i)
        {
            if(temp.at(i)==0x00)
            {
                x00 = i;
                break;
            }
        }
        if(x00<0)
        {
            emit Error("Błąd parsowania listy funkcjonalności");
            return;
        }
        QList<int> ptrs;
        for(int i=0;i<x00;++i)
            ptrs.append(temp.at(i));
        davClass tdv{tclass, ptrs};
        devClasses.append(tdv);
        temp.remove(0, x00+1);
    }

    ui->UpdateDevDescriptor(parsedDevDesc, devClasses);
}

/**
 * Funkcja przetwarza dane binarne methDescriptor na listę metod methods.
 */
void ZR3UIFrame::ParseMethods()
{
    if(stringi.isEmpty())
        return;
    if(methDescriptor.isEmpty())
        return;

    QByteArray temp = methDescriptor;
    methods.clear();

    while(!temp.isEmpty())
    {
        QList<param> par;
        method met{(char)0xFF, false, false, false, 0, (char)0xFF, "-", "-", par};

        if(temp.size()<3)
        {
            emit Error("Błąd parsowania deskryptora metod: temp.size()<3");
            return;
        }
        met.header = temp.at(0);
        met.secondHeader = temp.at(2);
        met.direct = temp.at(1)&0x80;
        met.isResponse = temp.at(1)&0x40;
        met.autoReport = temp.at(1)&0x20;
        met.timeout = (temp.at(1)&0x1F)*50;
        temp.remove(0, 3);

        try
        {
            met.tooltip = ReadAndRemoveNextString(temp);
            met.desc = ReadAndRemoveNextString(temp);
        }
        catch(QString exc)
        {
            emit Error(exc);
            return;
        }

        while(1)
        {
            if(temp.isEmpty())
            {
                emit Error("Błąd parsowania deskryptora metod: temp.isEmpty() in params");
                return;
            }
            if(temp.at(0)==(char)0xFF)
            {
                temp.remove(0, 1);
                break;
            }
            param par{"-", "-", "-", "-"};

            try
            {
                par.type = ReadAndRemoveNextSimpleString(temp);
                par.unit = ReadAndRemoveNextSimpleString(temp);
                par.tooltip = ReadAndRemoveNextString(temp);
                par.desc = ReadAndRemoveNextString(temp);
            }
            catch(QString exc)
            {
                emit Error(exc);
                return;
            }

            met.params.append(par);
        }
        methods.append(met);
    }

    ui->UpdateMetDescriptor(methods);

    for(method m: methods)
    {
        qDebug() << (uchar)m.header << m.direct << m.isResponse << m.autoReport << m.timeout << (uchar)m.secondHeader << m.tooltip << m.desc;
        for(param p: m.params)
            qDebug() << "\t\t" << p.type << p.unit << p.tooltip << p.desc;
    }
}

/**
 * Odczytuje z ciągu binarnego początkowy zbiór wartości (jednobajtywych) aż do napotkania znacznika 0xFF i usuwa je z danych. Odczytane liczby
 * trantuje jako wskaźniki do listy stringów i składa je w jeden ciąg tekstowy.
 * @param arr - dane binarne
 * @return tekst wynikowy
 */
QString ZR3UIFrame::ReadAndRemoveNextString(QByteArray& arr) throw(QString)
{
    int xff = -1;
    QList<int> ptrs;

    for(int i=0;i<arr.size();++i)
    {
        if((arr.at(i)==(char)0xFF))
        {
            xff = i;
            break;
        }
    }
    if(xff<0)
        throw QString("Błąd parsowania stringów: nie odnaleziono znacznika 0xFF");
    for(int i=0;i<xff;++i)
        ptrs.append(arr.at(i));
    QString temp = ConcStringPointers(ptrs, currentLang);
    arr.remove(0, xff+1);
    return temp;
}

/**
 * Odczytuje z ciągu binarnego początkowy ciąg znaków (do pierwszego znacznika 0x00) i usuwa go z danych.
 * @param arr - dane binarne
 * @return tekst wynikowy
 */
QString ZR3UIFrame::ReadAndRemoveNextSimpleString(QByteArray& arr) throw(QString)
{
    int x00 = -1;
    for(int i=0;i<arr.size();++i)
    {
        if(arr.at(i)==0x00)
        {
            x00 = i;
            break;
        }
    }
    if(x00<0)
        throw QString("Błąd parsowania stringów: nie odnaleziono znacznika 0x00");
    QString temp = arr.mid(0, x00);
    arr.remove(0, x00+1);
    return temp;
}

/**
 * Składa ciąg tekstowy na podstawie listy numerów stringów, wcześniej odczytanej listy stringóW (stringi) i numeru języka.
 * @param ptrs - lista numerów stringów
 * @param lang - numer języka
 * @return tekst wynikowy
 */
QString ZR3UIFrame::ConcStringPointers(QList<int> ptrs, int lang) throw(QString)
{
    if(lang>=stringi.size())
        throw QString("Błąd konkatenacji listy stringów: nieprawidłowy numer języka: " + QString::number(lang));

    QStringList tempList = stringi.at(lang);
    QString temp;
    for(int i: ptrs)
    {
        i += 1;
        if(i>=tempList.size())
            throw QString("Błąd konkatenacji listy stringów: nieprawidłowy wskaźnik tekstu: " + QString::number(i));
        temp.append(" " + tempList.at(i));
    }
    if(temp.size()>0)
        temp.remove(0, 1);//usuwanie spacji na początku
    return temp;
}

void ZR3UIFrame::FrameToUI(QSharedPointer<Frame> frame)
{
    if(frame->pureData().at(3)==_adr)
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
        ParseMethods();
    }
}
