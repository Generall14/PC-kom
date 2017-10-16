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
    groupBoxWyslijCosX->addWidget(leHeader);

    QHBoxLayout* groupBoxWyslijCosY = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosY);
    QLabel* tl2 = new QLabel("Adres:");
    groupBoxWyslijCosY->addWidget(tl2);
    leAdr = new QLineEdit("fe");
    leAdr->setMaximumWidth(50);
    leAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    groupBoxWyslijCosY->addWidget(leAdr);

    QHBoxLayout* groupBoxWyslijCosZ = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosZ);
    QLabel* tl3 = new QLabel("Dane:");
    groupBoxWyslijCosZ->addWidget(tl3);
    leData = new QLineEdit("ff aa 55");
    leData->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    groupBoxWyslijCosZ->addWidget(leData);

    btn = new QPushButton("Wyślij coś");
    mainWyslijCosLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));



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
