#include "LogicUIStawrov.hpp"
#include "../Factory.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QTextStream>

LogicUIStawrov::LogicUIStawrov(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIStawrov";
    logg = new STawrovLogger("dupa.txt");
    connect(logg, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(logg, SIGNAL(StateChanged(QString)), this, SLOT(setStatus(QString)), Qt::QueuedConnection);
    connect(logg, SIGNAL(SetChannels(int)), this, SLOT(setChannels(int)), Qt::QueuedConnection);
    logg->Reset("defaultFileName.txt");
}

LogicUIStawrov::~LogicUIStawrov()
{
    QFile config1File;
    QTextStream out(&config1File);

    config1File.setFileName("configs/LogicUIStawrovAdr.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << leAdr->text();
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovHeader.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << leHeader->text();
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovData.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << leData->text();
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovFileLog.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << fileAdr->text();
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovleZakA.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << leZakA->text();
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovleAakB.cfg");
    if(config1File.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        out << leAakB->text();
        config1File.close();
    }

    delete logg;
}

void LogicUIStawrov::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitTests();

    QLabel* tempLabel = new QLabel("Nic tu nie ma");
    mainLay->addWidget(tempLabel);



    btnE = new QPushButton("Wygeneruj bezsensowny błąd");
    mainLay->addWidget(btnE);
    connect(btnE, SIGNAL(clicked(bool)), this, SLOT(makeStupidError()));

    LoadConfigs();
}

void LogicUIStawrov::InitTests()
{
    //=======================Grupa wyslijcos======================================================
    QGroupBox* groupBoxWyslijCos = new QGroupBox("Wyślij coś");
    mainLay->addWidget(groupBoxWyslijCos);
    QVBoxLayout* mainWyslijCosLay = new QVBoxLayout(groupBoxWyslijCos);

    QHBoxLayout* groupBoxWyslijCosX = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosX);
    QLabel* tl1 = new QLabel("Nagłówek:");
    groupBoxWyslijCosX->addWidget(tl1);
    leHeader = new QLineEdit("fd");
    leHeader->setMaximumWidth(50);
    leHeader->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leHeader->setValidator(new HexValidator(1, 1, leHeader));
    groupBoxWyslijCosX->addWidget(leHeader);

    QHBoxLayout* groupBoxWyslijCosY = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosY);
    QLabel* tl2 = new QLabel("Adres:");
    groupBoxWyslijCosY->addWidget(tl2);
    leAdr = new QLineEdit("fe");
    leAdr->setMaximumWidth(50);
    leAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leAdr->setValidator(new HexValidator(1, 1, leAdr));
    groupBoxWyslijCosY->addWidget(leAdr);

    QHBoxLayout* groupBoxWyslijCosZ = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosZ);
    QLabel* tl3 = new QLabel("Dane:");
    groupBoxWyslijCosZ->addWidget(tl3);
    leData = new QLineEdit("ff aa 55");
    leData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leData->setValidator(new HexValidator(1, 27, leData));
    groupBoxWyslijCosZ->addWidget(leData);

    btn = new QPushButton("Wyślij coś");
    mainWyslijCosLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    //=======================Grupa zbieranie danych===============================================
    QGroupBox* groupBoxZbieranie = new QGroupBox("Zbieranie danych");
    mainLay->addWidget(groupBoxZbieranie);
    QVBoxLayout* mainZbieranieLay = new QVBoxLayout(groupBoxZbieranie);

    QHBoxLayout* mainZbieranieLay1 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay1);
    QLabel* tlab = new QLabel("Status:");
    mainZbieranieLay1->addWidget(tlab);
    statusLabel = new QLabel("---");
    statusLabel->setAlignment(Qt::AlignRight);
    mainZbieranieLay1->addWidget(statusLabel);

    QHBoxLayout* mainZbieranieLay3 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay3);
    tlab = new QLabel("Kanały:");
    mainZbieranieLay3->addWidget(tlab);
    channelsLabel = new QLabel("-");
    channelsLabel->setAlignment(Qt::AlignRight);
    mainZbieranieLay3->addWidget(channelsLabel);

    QHBoxLayout* mainZbieranieLay2 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay2);
    QLabel* lll = new QLabel("Nazwa pliku:");
    mainZbieranieLay2->addWidget(lll);
    fileAdr = new QLineEdit("defaultFileName.txt");
    mainZbieranieLay2->addWidget(fileAdr);

    QPushButton* btnr = new QPushButton("Reset");
    mainZbieranieLay->addWidget(btnr);
    connect(btnr, &QPushButton::clicked, [=](){logg->Reset(fileAdr->text());});

    //=======================Grupa konfiguracja===================================================
    QGroupBox* groupBoxKonfiguracja = new QGroupBox("Konfiguracja kontrolerów");
    mainLay->addWidget(groupBoxKonfiguracja);
    QVBoxLayout* mainKonfiguracjaLay = new QVBoxLayout(groupBoxKonfiguracja);

    QHBoxLayout* groupBoxKonfiguracja1 = new QHBoxLayout();
    mainKonfiguracjaLay->addLayout(groupBoxKonfiguracja1);
    tl1 = new QLabel("Zakres pracy (min - max):");
    groupBoxKonfiguracja1->addWidget(tl1);
    leZakA = new QLineEdit("fd");
    leZakA->setMaximumWidth(50);
    leZakA->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leZakA->setValidator(new HexValidator(2, 1, leZakA));
    groupBoxKonfiguracja1->addWidget(leZakA);
    leAakB = new QLineEdit("fd");
    leAakB->setMaximumWidth(50);
    leAakB->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leAakB->setValidator(new HexValidator(2, 1, leAakB));
    groupBoxKonfiguracja1->addWidget(leAakB);


    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUIStawrov::LoadConfigs()
{
    QFile config1File;

    config1File.setFileName("configs/LogicUIStawrovAdr.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        leAdr->setText(QString(config1File.readLine()));
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovHeader.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        leHeader->setText(QString(config1File.readLine()));
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovData.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        leData->setText(QString(config1File.readLine()));
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovFileLog.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        fileAdr->setText(QString(config1File.readLine()));
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovleZakA.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        leZakA->setText(QString(config1File.readLine()));
        config1File.close();
    }

    config1File.setFileName("configs/LogicUIStawrovleAakB.cfg");
    if(config1File.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        leAakB->setText(QString(config1File.readLine()));
        config1File.close();
    }
}

void LogicUIStawrov::Connected()
{
    btn->setEnabled(true);
}

void LogicUIStawrov::Disconnected()
{
    btn->setEnabled(false);
}

void LogicUIStawrov::FrameReaded(QSharedPointer<Frame> frame)
{
    logg->FrameReaded(frame);
    frame.isNull();
}

void LogicUIStawrov::makeStupidMessage()
{
    QByteArray maker;
    maker.append(0xFF);

    QString stemp = leHeader->text().left(2);
    int tint = 0;
    bool ok;
    tint = stemp.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane nagłówka \""+stemp+"\".");
        return;
    }
    maker.append(tint&0xFF);

    stemp = leAdr->text().left(2);
    tint = stemp.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+stemp+"\".");
        return;
    }
    maker.append(tint&0xFF);

    QByteArray dataArray;
    for(QString tttemp: leData->text().split(" "))
    {
        stemp = tttemp.left(2);
        if(stemp.isEmpty())
            continue;
        tint = stemp.toInt(&ok, 16);
        if(!ok)
        {
            emit Error("Kijowe dane danych \""+stemp+"\".");
            return;
        }
        dataArray.append(tint&0xFF);
    }

    maker.append(dataArray.size()&0xFF);
    maker.append(dataArray);
    maker = FrameStawrov::AddCRC16(maker);

    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(maker)));
}

void LogicUIStawrov::makeStupidError()
{
    emit Error("Bezsensowny błąd.");
}

void LogicUIStawrov::setStatus(QString s)
{
    statusLabel->setText(s);
}

void LogicUIStawrov::setChannels(int s)
{
    channelsLabel->setText(QString::number(s));
}
