#include "LogicUISG-1.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGroupBox>
#include <QSpacerItem>

LogicUISG1::LogicUISG1(QFrame* parent):
    LogicUI(parent)
{

}

void LogicUISG1::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

    QTabWidget* tw = new QTabWidget();
    mainLay->addWidget(tw);


    dbgFrame = new QFrame();
    tw->addTab(dbgFrame, "Debug");
    InitDebug();


    calFrame = new QFrame();
    tw->addTab(calFrame, "Kalibracja");
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
    btnHello = new QPushButton("Hello");
    bbbhello->addWidget(btnHello);
    btnHello->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblHello = new QLabel("Prot. vX.XXt, prog. vX.XXt");
    bbbhello->addWidget(lblHello);
    lblHello->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbcounts = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbcounts);
    btnCounts = new QPushButton("Zliczenia");
    bbbcounts->addWidget(btnCounts);
    btnCounts->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblCounts = new QLabel("XXX imp/s");
    bbbcounts->addWidget(lblCounts);
    lblCounts->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbblevels = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbblevels);
    btnLevels = new QPushButton("Poziomy");
    bbblevels->addWidget(btnLevels);
    btnLevels->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblLevels = new QLabel("X/X");
    bbblevels->addWidget(lblLevels);
    lblLevels->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbzatk = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbzatk);
    btnZatk = new QPushButton("Zatkanie");
    bbbzatk->addWidget(btnZatk);
    btnZatk->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblZatk = new QLabel("XXX ADC");
    bbbzatk->addWidget(lblZatk);
    lblZatk->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbtemp = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbtemp);
    btnTemp = new QPushButton("Temp.");
    bbbtemp->addWidget(btnTemp);
    btnTemp->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblTemp = new QLabel("XXX ADC");
    bbbtemp->addWidget(lblTemp);
    lblTemp->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbvsipm = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbvsipm);
    btnVSiPM = new QPushButton("V SiPM");
    bbbvsipm->addWidget(btnVSiPM);
    btnVSiPM->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblVSiPM = new QLabel("XXX DAC");
    bbbvsipm->addWidget(lblVSiPM);
    lblVSiPM->setAlignment(Qt::AlignRight);

    QHBoxLayout* bbbvbat = new QHBoxLayout();
    mainZapytaniaLay->addLayout(bbbvbat);
    btnVBat = new QPushButton("V Bat.");
    bbbvbat->addWidget(btnVBat);
    btnVBat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lblVBat = new QLabel("XXX V");
    bbbvbat->addWidget(lblVBat);
    lblVBat->setAlignment(Qt::AlignRight);

    //=======================Grupa wymuszenia=====================================================
    QGroupBox* groupBoxWymuszenia = new QGroupBox("Wymuszenia");
    mainDbgLay->addWidget(groupBoxWymuszenia);
    QHBoxLayout* mainWymuszeniaLay = new QHBoxLayout(groupBoxWymuszenia);

    btnACal = new QPushButton("A. kal.");
    mainWymuszeniaLay->addWidget(btnACal);
    btnACal->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    mainWymuszeniaLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    btnRst = new QPushButton("Reset");
    mainWymuszeniaLay->addWidget(btnRst);
    btnRst->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

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
    btnARep = new QPushButton("Zapisz");
    chklay3->addWidget(btnARep);
    btnARep->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);


    QHBoxLayout* chklayb = new QHBoxLayout();
    mainRaportyLay->addLayout(chklayb);
    chklayb->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));


    //=======================Grupa kalibracja=====================================================
    QGroupBox* groupBoxKalibracja = new QGroupBox("Kalibracja");
    mainDbgLay->addWidget(groupBoxKalibracja);
    QVBoxLayout* mainKalibracjaLay = new QVBoxLayout(groupBoxKalibracja);

    QHBoxLayout* kallay = new QHBoxLayout();
    mainKalibracjaLay->addLayout(kallay);

    QVBoxLayout* kallay1 = new QVBoxLayout();
    kallay->addLayout(kallay1);
    k00 = new QLabel("XXX");
    k00->setAlignment(Qt::AlignCenter);
    kallay1->addWidget(k00);
    k10 = new QLabel("XXX");
    k10->setAlignment(Qt::AlignCenter);
    kallay1->addWidget(k10);
    k20 = new QLabel("XXX");
    k20->setAlignment(Qt::AlignCenter);
    kallay1->addWidget(k20);
    k30 = new QLabel("XXX");
    k30->setAlignment(Qt::AlignCenter);
    kallay1->addWidget(k30);

    QVBoxLayout* kallay2 = new QVBoxLayout();
    kallay->addLayout(kallay2);
    k01 = new QLabel("XXX");
    k01->setAlignment(Qt::AlignCenter);
    kallay2->addWidget(k01);
    k11 = new QLabel("XXX");
    k11->setAlignment(Qt::AlignCenter);
    kallay2->addWidget(k11);
    k21 = new QLabel("XXX");
    k21->setAlignment(Qt::AlignCenter);
    kallay2->addWidget(k21);
    k31 = new QLabel("XXX");
    k31->setAlignment(Qt::AlignCenter);
    kallay2->addWidget(k31);

    QVBoxLayout* kallay3 = new QVBoxLayout();
    kallay->addLayout(kallay3);
    k02 = new QLabel("XXX");
    k02->setAlignment(Qt::AlignCenter);
    kallay3->addWidget(k02);
    k12 = new QLabel("XXX");
    k12->setAlignment(Qt::AlignCenter);
    kallay3->addWidget(k12);
    k22 = new QLabel("XXX");
    k22->setAlignment(Qt::AlignCenter);
    kallay3->addWidget(k22);
    k32 = new QLabel("XXX");
    k32->setAlignment(Qt::AlignCenter);
    kallay3->addWidget(k32);

    QHBoxLayout* kkkread = new QHBoxLayout();
    mainKalibracjaLay->addLayout(kkkread);
    sbrnumber = new QSpinBox();
    kkkread->addWidget(sbrnumber);
    sbrnumber->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbrnumber->setMaximum(11);
    kalread = new QPushButton("Read");
    kkkread->addWidget(kalread);
    kalread->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    kkkread->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    kalreadall = new QPushButton("Read all");
    kkkread->addWidget(kalreadall);
    kalreadall->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

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
    kalwrite = new QPushButton("Zapisz");
    kkkread2->addWidget(kalwrite);
    kalwrite->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);




    mainDbgLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
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
    QByteArray pck = frame->pureData();
    if(pck.length()<5)
        return;

    const float timeres = 0.5, kb=3.3/1024.0;
    float voltage;
    int mlv=0, llv=0, pga, pgb, pra, prb;
    QString pgt, prt;

    int val = 0;
    val |= (pck[1]<<16)&0xFF0000;
    val |= (pck[2]<<8)&0xFF00;
    val |= pck[3]&0xFF;

    switch (pck.at(0))
    {
    case 'C':                           //Pomiar
        lblCounts->setText(QString::number(val/timeres)+" imp/s");
        return;
    case 'T':                           //Temperatura
        lblTemp->setText(QString("%1 ADC").arg(val, 8, 10));
        return;
    case 'Z':                           //Zatkanie
        lblZatk->setText(QString("%1 ADC").arg(val, 8, 10));
        return;
    case 'L':                           //Poziomy
        mlv=0;
        llv=0;
        mlv |= pck[2]&0xFF;
        llv |= pck[3]&0xFF;
        llv = 8-llv;
        lblLevels->setText(QString("%1/%2").arg(mlv, 0, 10).arg(llv, 0, 10));
        return;
    case 'D':                           //Napięcie SiPM
        lblVSiPM->setText(QString("%1 DAC").arg(val, 0, 10));
        return;
//    case 'H':                           //Hello
//        pga=0;
//        pga=(pck[3]>>4)&0x07;
//        pgb=0;
//        pgb=(pck[3]&0x0F);
//        pra=0;
//        pra=(pck[2]>>4)&0x07;
//        prb=0;
//        prb=(pck[2]&0x0F);
//        pgt = "";
//        prt = "";
//        if(pck[3]&0x80)
//            pgt="t";
//        if(pck[2]&0x80)
//            prt="t";
//        return QString("Hello: program v%1.%2").arg(pga, 0, 10).arg(pgb, 0, 10)+pgt+QString(", protokół v%1.%2").arg(pra, 0, 10).arg(prb, 0, 10)+prt+".";
    case 'V':                           //napięcie baterii
        voltage = (float)val*kb;
        lblVBat->setText(QString::number(voltage)+" V");
        return;
    }
}
