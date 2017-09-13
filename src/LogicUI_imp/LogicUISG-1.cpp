#include "LogicUISG-1.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGroupBox>
#include <QSpacerItem>
#include "utils/Transaction.hpp"
#include "utils/WorkerManager.hpp"

LogicUISG1::LogicUISG1(QFrame* parent):
    LogicUI(parent)
{

}

void LogicUISG1::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

    QTabWidget* tw = new QTabWidget();
    mainLay->addWidget(tw);

    errorLabel = new QLabel("");
    standardPalette = errorLabel->palette();
    errorPalette = standardPalette;
    errorPalette.setColor(QPalette::WindowText, Qt::black);
    errorPalette.setColor(QPalette::Window, Qt::red);
    errorLabel->setAutoFillBackground(true);
    cParent->setAutoFillBackground(true);
    mainLay->addWidget(errorLabel);

    dbgFrame = new QFrame();
    tw->addTab(dbgFrame, "Debug");
    InitDebug();

    calFrame = new QFrame();
    tw->addTab(calFrame, "Kalibracja");
    InitCal();
}

void LogicUISG1::InitDebug()
{
    QVBoxLayout* mainDbgLay = new QVBoxLayout(dbgFrame);

    //=======================Grupa zapytania======================================================
    QGroupBox* groupBoxZapytania = new QGroupBox("Zapytania");
    mainDbgLay->addWidget(groupBoxZapytania);
    QVBoxLayout* mainZapytaniaLay = new QVBoxLayout(groupBoxZapytania);

    QHBoxLayout* bbbhello = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbhello);
    QPushButton* btnHello = new QPushButton("Hello");
    bbbhello->addWidget(btnHello);
    btnHello->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnHello, &QPushButton::clicked, [=](){SendFrame('h');});
    lblHello = new QLabel("prog. vX.XXx, prot. vX.XXx");
    bbbhello->addWidget(lblHello);
    lblHello->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbcounts = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbcounts);
    QPushButton* btnCounts = new QPushButton("Zliczenia");
    bbbcounts->addWidget(btnCounts);
    btnCounts->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnCounts, &QPushButton::clicked, [=](){SendFrame('c');});
    lblCounts = new QLabel("XXX imp/s");
    bbbcounts->addWidget(lblCounts);
    lblCounts->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbblevels = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbblevels);
    QPushButton* btnLevels = new QPushButton("Poziomy");
    bbblevels->addWidget(btnLevels);
    btnLevels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnLevels, &QPushButton::clicked, [=](){SendFrame('l');});
    lblLevels = new QLabel("X/X");
    bbblevels->addWidget(lblLevels);
    lblLevels->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbzatk = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbzatk);
    QPushButton* btnZatk = new QPushButton("Zatkanie");
    bbbzatk->addWidget(btnZatk);
    btnZatk->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnZatk, &QPushButton::clicked, [=](){SendFrame('z');});
    lblZatk = new QLabel("XXX ADC");
    bbbzatk->addWidget(lblZatk);
    lblZatk->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbtemp = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbtemp);
    QPushButton* btnTemp = new QPushButton("Temp.");
    bbbtemp->addWidget(btnTemp);
    btnTemp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnTemp, &QPushButton::clicked, [=](){SendFrame('t');});
    lblTemp = new QLabel("XXX ADC");
    bbbtemp->addWidget(lblTemp);
    lblTemp->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbvsipm = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbvsipm);
    QPushButton* btnVSiPM = new QPushButton("V SiPM");
    bbbvsipm->addWidget(btnVSiPM);
    btnVSiPM->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnVSiPM, &QPushButton::clicked, [=](){SendFrame('d');});
    lblVSiPM = new QLabel("XXX DAC");
    bbbvsipm->addWidget(lblVSiPM);
    lblVSiPM->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbvbat = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbvbat);
    QPushButton* btnVBat = new QPushButton("V Bat.");
    bbbvbat->addWidget(btnVBat);
    btnVBat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnVBat, &QPushButton::clicked, [=](){SendFrame('v');});
    lblVBat = new QLabel("XXX V");
    bbbvbat->addWidget(lblVBat);
    lblVBat->setAlignment(Qt::AlignRight);

    //=======================Grupa wymuszenia=====================================================
    QGroupBox* groupBoxWymuszenia = new QGroupBox("Wymuszenia");
    mainDbgLay->addWidget(groupBoxWymuszenia);
    QHBoxLayout* mainWymuszeniaLay = new QHBoxLayout(groupBoxWymuszenia);

    QPushButton* btnACal = new QPushButton("A. kal.");
    mainWymuszeniaLay->addWidget(btnACal);
    btnACal->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnACal, &QPushButton::clicked, [=](){SendFrame('a');});

    mainWymuszeniaLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnRst = new QPushButton("Reset");
    mainWymuszeniaLay->addWidget(btnRst);
    btnRst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnRst, &QPushButton::clicked, [=](){SendFrame('r');});

    //=======================Grupa raporty========================================================
    QGroupBox* groupBoxRaporty = new QGroupBox("Raporty");
    mainDbgLay->addWidget(groupBoxRaporty);
    QVBoxLayout* mainRaportyLay = new QVBoxLayout(groupBoxRaporty);

    QHBoxLayout* chklay = new QHBoxLayout();
    mainRaportyLay->addLayout(chklay);

    QVBoxLayout* chklay1 = new QVBoxLayout();
    chklay->addLayout(chklay1);
    chkCounts = new QCheckBox("Cnt");
    chklay1->addWidget(chkCounts);
    chkTemp = new QCheckBox("Temp.");
    chklay1->addWidget(chkTemp);
    chkVSiPM = new QCheckBox("VSiPM");
    chklay1->addWidget(chkVSiPM);

    QVBoxLayout* chklay2 = new QVBoxLayout();
    chklay->addLayout(chklay2);
    chkZatk = new QCheckBox("Zatk.");
    chklay2->addWidget(chkZatk);
    chkLevels = new QCheckBox("Poz.");
    chklay2->addWidget(chkLevels);
    chkACal = new QCheckBox("A. Kal.");
    chklay2->addWidget(chkACal);

    QVBoxLayout* chklay3 = new QVBoxLayout();
    chklay->addLayout(chklay3);
    QPushButton* btnARep = new QPushButton("Zapisz");
    chklay3->addWidget(btnARep);
    btnARep->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(btnARep, &QPushButton::clicked, this, &LogicUISG1::SendAutoReportConfig);


    QHBoxLayout* chklayb = new QHBoxLayout();
    mainRaportyLay->addLayout(chklayb);
    chklayb->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));


    //=======================Grupa kalibracja=====================================================
    for(int i=0;i<12;++i)
    {
        calV.push_back(new QLabel("XXX"));
        calV.at(i)->setAlignment(Qt::AlignCenter);
    }
    QGroupBox* groupBoxKalibracja = new QGroupBox("Kalibracja");
    mainDbgLay->addWidget(groupBoxKalibracja);
    QVBoxLayout* mainKalibracjaLay = new QVBoxLayout(groupBoxKalibracja);

    QHBoxLayout* kallay = new QHBoxLayout();
    mainKalibracjaLay->addLayout(kallay);

    QVBoxLayout* kallay1 = new QVBoxLayout();
    kallay->addLayout(kallay1);
    kallay1->addWidget(calV.at(0));
    kallay1->addWidget(calV.at(3));
    kallay1->addWidget(calV.at(6));
    kallay1->addWidget(calV.at(9));

    QVBoxLayout* kallay2 = new QVBoxLayout();
    kallay->addLayout(kallay2);
    kallay2->addWidget(calV.at(1));
    kallay2->addWidget(calV.at(4));
    kallay2->addWidget(calV.at(7));
    kallay2->addWidget(calV.at(10));

    QVBoxLayout* kallay3 = new QVBoxLayout();
    kallay->addLayout(kallay3);
    kallay3->addWidget(calV.at(2));
    kallay3->addWidget(calV.at(5));
    kallay3->addWidget(calV.at(8));
    kallay3->addWidget(calV.at(11));

    QHBoxLayout* kkkread = new QHBoxLayout();
    mainKalibracjaLay->addLayout(kkkread);
    sbrnumber = new QSpinBox();
    kkkread->addWidget(sbrnumber);
    sbrnumber->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbrnumber->setMaximum(11);
    QPushButton* kalread = new QPushButton("Read");
    kkkread->addWidget(kalread);
    kalread->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    kkkread->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    connect(kalread, &QPushButton::clicked, this, &LogicUISG1::ReadSingleCal);
    QPushButton* kalreadall = new QPushButton("Read all");
    kkkread->addWidget(kalreadall);
    kalreadall->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(kalreadall, &QPushButton::clicked, this, &LogicUISG1::ReadAll);

    QHBoxLayout* kkkread2 = new QHBoxLayout();
    mainKalibracjaLay->addLayout(kkkread2);
    sbwnumber = new QSpinBox();
    kkkread2->addWidget(sbwnumber);
    sbwnumber->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbwnumber->setMaximum(11);
    sbwvalue = new QSpinBox();
    kkkread2->addWidget(sbwvalue);
    sbwvalue->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbwvalue->setMaximum(120000);
    kkkread2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QPushButton* kalwrite = new QPushButton("Zapisz");
    kkkread2->addWidget(kalwrite);
    kalwrite->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(kalwrite, &QPushButton::clicked, this, &LogicUISG1::WriteSingleCal);



    mainDbgLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUISG1::InitCal()
{
    QVBoxLayout* mainCalLay = new QVBoxLayout(calFrame);

    //=======================Zbieranie danych=====================================================
    QGroupBox* groupBoxZbieranie = new QGroupBox("Zbieranie danych");
    mainCalLay->addWidget(groupBoxZbieranie);
    QVBoxLayout* mainZbieranieLay = new QVBoxLayout(groupBoxZbieranie);

    QHBoxLayout* bbbzlierajz = new QHBoxLayout();
    mainZbieranieLay->addLayout(bbbzlierajz);
    QVBoxLayout* xxx1 = new QVBoxLayout();
    bbbzlierajz->addLayout(xxx1);
    QLabel* tlab0 = new QLabel("Zbieraj z ");
    xxx1->addWidget(tlab0);
    QVBoxLayout* xxx2 = new QVBoxLayout();
    bbbzlierajz->addLayout(xxx2);
    chkProbki = new QSpinBox();
    chkProbki->setMinimum(2);
    chkProbki->setMaximum(100000);
    chkProbki->setValue(120);
    xxx2->addWidget(chkProbki);
    QVBoxLayout* xxx3 = new QVBoxLayout();
    bbbzlierajz->addLayout(xxx3);
    rbtRap = new QRadioButton("raportów");
    xxx3->addWidget(rbtRap);
    rbtImp = new QRadioButton("impulsów");
    xxx3->addWidget(rbtImp);
    rbtRap->setChecked(true);

    chkContin = new QCheckBox("Pomiar ciągły");
    mainZbieranieLay->addWidget(chkContin);


    QHBoxLayout* bbbblierajz = new QHBoxLayout();
    mainZbieranieLay->addLayout(bbbblierajz);

    QPushButton* btnStop = new QPushButton("Stop");
    bbbblierajz->addWidget(btnStop);
    btnStop->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    bbbblierajz->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QPushButton* btnStart = new QPushButton("Start");
    bbbblierajz->addWidget(btnStart);
    btnStart->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    //=======================Pomiar===============================================================
    QFrame* mFrame = new QFrame();
    QPalette tempp = mFrame->palette();
    tempp.setColor(QPalette::WindowText, QColor(240, 180, 0));
    tempp.setColor(QPalette::Window, QColor(0, 120, 0));
    mFrame->setAutoFillBackground(true);
    mFrame->setPalette(tempp);
    mainCalLay->addWidget(mFrame);
    QVBoxLayout* mFramelayout = new QVBoxLayout(mFrame);

    mPomiar = new QLabel("- cps");
    QFont temp = mPomiar->font();
    temp.setPointSize(28);
    temp.setBold(true);
    mPomiar->setFont(temp);
    mPomiar->setAlignment(Qt::AlignCenter);
    mFramelayout->addWidget(mPomiar);

    sPomiar = new QLabel("- ADC");
    sPomiar->setAlignment(Qt::AlignRight);
    mFramelayout->addWidget(sPomiar);

    progressBar = new QProgressBar();
    progressBar->setMaximum(1000);
    progressBar->setValue(0);
    mFramelayout->addWidget(progressBar);

    //=======================Punkty kontrolne=====================================================
    QGroupBox* groupBoxPunkty = new QGroupBox("Punkty kalibracyjne");
    mainCalLay->addWidget(groupBoxPunkty);
    QHBoxLayout* mainPunktyLay = new QHBoxLayout(groupBoxPunkty);

    QVBoxLayout* bbbklierajz = new QVBoxLayout();
    mainPunktyLay->addLayout(bbbklierajz);

    QPushButton* btnUsun = new QPushButton("Usuń");
    bbbklierajz->addWidget(btnUsun);
    btnUsun->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton* btnDodaj = new QPushButton("Dodaj");
    bbbklierajz->addWidget(btnDodaj);
    btnDodaj->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    bbbklierajz->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    lstKal = new QListWidget();
    lstKal->setMaximumWidth(150);
    lstKal->setMaximumHeight(150);
    lstKal->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    mainPunktyLay->addWidget(lstKal);

    //=======================Punkty docelowe======================================================
    QVector<int> defaultTrs = {0, 100, 1000, 2, 10, 100, 10, 100, 500, 80, 300, 1000};
    for(int i=0;i<12;++i)
    {
        calDst.push_back(new QSpinBox());
        calDst.at(i)->setMaximum(1100);
        calDst.at(i)->setValue(defaultTrs.at(i));
    }
    QGroupBox* groupBoxDst = new QGroupBox("Progi docelowe [uSv/h]");
    mainCalLay->addWidget(groupBoxDst);
    QHBoxLayout* mainDstLay = new QHBoxLayout(groupBoxDst);

    QVBoxLayout* kallay1 = new QVBoxLayout();
    mainDstLay->addLayout(kallay1);
    kallay1->addWidget(calDst.at(0));
    kallay1->addWidget(calDst.at(3));
    kallay1->addWidget(calDst.at(6));
    kallay1->addWidget(calDst.at(9));

    QVBoxLayout* kallay2 = new QVBoxLayout();
    mainDstLay->addLayout(kallay2);
    kallay2->addWidget(calDst.at(1));
    kallay2->addWidget(calDst.at(4));
    kallay2->addWidget(calDst.at(7));
    kallay2->addWidget(calDst.at(10));

    QVBoxLayout* kallay3 = new QVBoxLayout();
    mainDstLay->addLayout(kallay3);
    kallay3->addWidget(calDst.at(2));
    kallay3->addWidget(calDst.at(5));
    kallay3->addWidget(calDst.at(8));
    kallay3->addWidget(calDst.at(11));


    //=======================Dane kalibracyjne====================================================
    QGroupBox* groupBoxDane = new QGroupBox("Parametry kalibracyjne");
    mainCalLay->addWidget(groupBoxDane);
    QVBoxLayout* mainDaneLay = new QVBoxLayout(groupBoxDane);

    QHBoxLayout* bbbzdane = new QHBoxLayout();
    mainDaneLay->addLayout(bbbzdane);
    QLabel* tlab1 = new QLabel("Metoda: ");
    bbbzdane->addWidget(tlab1);
    cmbMetoda = new QComboBox();
    bbbzdane->addWidget(cmbMetoda);

    QHBoxLayout* bbbzdanez = new QHBoxLayout();
    mainDaneLay->addLayout(bbbzdanez);
    QPushButton* megabutton = new QPushButton("Wygeneruj dane i zapisz do SG-1");
    bbbzdanez->addWidget(megabutton);



    mainCalLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUISG1::Connected()
{
    dbgFrame->setEnabled(true);
    calFrame->setEnabled(true);
}

void LogicUISG1::Disconnected()
{
    dbgFrame->setEnabled(false);
    calFrame->setEnabled(false);
}

void LogicUISG1::FrameReaded(QSharedPointer<Frame> frame)
{
    if(!frame->isValid())
        return;

    if(errorCounter)
        errorCounter--;
    else
    {
        errorLabel->setPalette(standardPalette);
        cParent->setPalette(standardPalette);
        errorLabel->setText("");
    }

    emit InternalFrameReaded(frame->pureData());

    QByteArray pck = frame->pureData();

    int ival=0;
    int inum=pck.at(0)&0x0F;
    ival |= (pck.at(1)<<16)&0xFF0000;
    ival |= (pck.at(2)<<8)&0x00FF00;
    ival |= (pck.at(3)<<0)&0x0000FF;
    if((pck[0]&0xF0)==0x10)
        return calV.at(inum)->setText(QString::number(ival));

    switch (pck.at(0))
    {
    case 'C':                           //Pomiar
        lblCounts->setText(frame->toShortQString());
        return;
    case 'T':                           //Temperatura
        lblTemp->setText(frame->toShortQString());
        return;
    case 'Z':                           //Zatkanie
        lblZatk->setText(frame->toShortQString());
        return;
    case 'L':                           //Poziomy
        lblLevels->setText(frame->toShortQString());
        return;
    case 'D':                           //Napięcie SiPM
        lblVSiPM->setText(frame->toShortQString());
        return;
    case 'H':                           //Hello
        lblHello->setText(frame->toShortQString());
        return;
    case 'V':                           //Napięcie baterii
        lblVBat->setText(frame->toShortQString());
        return;
    case 'E':                           //Błąd
        errorLabel->setPalette(errorPalette);
        cParent->setPalette(errorPalette);
        errorLabel->setText("ERROR: "+frame->toShortQString());
        errorCounter = 1;
        return;
    }
}

void LogicUISG1::SendFrame(uchar header, int val)
{
    emit WriteFrame(MakeFrame(header, val));
}

QSharedPointer<Frame> LogicUISG1::MakeFrame(uchar header, int val)
{
    QByteArray temp;
    temp.append(header);
    temp.append((val>>16)&0xFF);
    temp.append((val>>8)&0xFF);
    temp.append((val>>0)&0xFF);
    temp.append(((int)header)^0xFF);
    return QSharedPointer<Frame>(Factory::newFrame(temp));
}

void LogicUISG1::SendAutoReportConfig()
{
    int tval = 0;
    if(chkCounts->isChecked())
        tval |= 1<<0;
    if(chkACal->isChecked())
        tval |= 1<<2;
    if(chkVSiPM->isChecked())
        tval |= 1<<3;
    if(chkTemp->isChecked())
        tval |= 1<<4;
    if(chkLevels->isChecked())
        tval |= 1<<5;
    if(chkZatk->isChecked())
        tval |= 1<<6;

    SendFrame('s', tval);
}

void LogicUISG1::ReadSingleCal()
{
    int header = 0x00;
    header += sbrnumber->value();
    SendFrame(header&0xFF);
}

void LogicUISG1::WriteSingleCal()
{
    int header = 0x20;
    header += sbwnumber->value();
    SendFrame(header&0xFF, sbwvalue->value());
}

void LogicUISG1::ReadAll()
{
    QVector<transaction> vec;
    for(int i=0;i<12;++i)
        vec.append(transaction(MakeFrame((0x00|i)&0xFF), QByteArray(1, (0x10|i)&0xFF), 1000, 3));

    WorkerManager* man = new WorkerManager(vec, 7);
    connect(this, SIGNAL(InternalFrameReaded(QByteArray)), man, SLOT(RecievedFrame(QByteArray)));
    connect(man, SIGNAL(SendFrame(QByteArray)), this, SLOT(InternalWriteFrame(QByteArray)));
    connect(man, SIGNAL(Fail(QString)), this, SIGNAL(Error(QString)));
    connect(man, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    man->start(QThread::HighPriority);
}

void LogicUISG1::InternalWriteFrame(QByteArray frame)
{
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(frame)));
}
