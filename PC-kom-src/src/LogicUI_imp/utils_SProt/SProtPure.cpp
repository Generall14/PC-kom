#include "SProtPure.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGroupBox>
#include <QSpacerItem>
#include "../../Utils/ValidateHex.hpp"
#include "../../Utils/StaticUtils.hpp"
#include "../../Frame_imp/FrameSProt.hpp"

SProtPure::SProtPure(QFrame* parent):
    LogicUI(parent),
    Restorable("SProtPure")
{
    Desc::description = "SProtPure";
}

SProtPure::~SProtPure()
{
    Store("lecmd", lecmd->text());
    Store("ledata", ledata->text());
    Store("ledatas", ledatas->text());
    Store("lesecnr", lesecnr->text());
    Store("lesecoff", lesecoff->text());
}

void SProtPure::restore()
{
    lecmd->setText(RestoreAsString("lecmd", "000"));
    ledata->setText(RestoreAsString("ledata", "61 62 63"));
    ledatas->setText(RestoreAsString("ledatas", "61 62 63"));
    lesecnr->setText(RestoreAsString("lesecnr", "01"));
    lesecoff->setText(RestoreAsString("lesecoff", "0000"));
}

void SProtPure::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QGroupBox* groupBoxData = new QGroupBox("Pure");
    mainLay->addWidget(groupBoxData);
    QVBoxLayout* dataMainLay = new QVBoxLayout(groupBoxData);


    QHBoxLayout* layBoxData0 = new QHBoxLayout();
    dataMainLay->addLayout(layBoxData0);

    QLabel* lab = new QLabel("Data:");
    layBoxData0->addWidget(lab);

    ledata = new QLineEdit("FF");
    ledata->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ledata->setValidator(new HexValidator(1, 20, ledata));
    layBoxData0->addWidget(ledata);


    QHBoxLayout* layBoxData = new QHBoxLayout();
    dataMainLay->addLayout(layBoxData);

    lab = new QLabel("Cmd:");
    layBoxData->addWidget(lab);

    lecmd = new QLineEdit("FF");
    lecmd->setMaximumWidth(50);
    lecmd->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lecmd->setValidator(new HexValidator(2, 1, lecmd));
    layBoxData->addWidget(lecmd);

    layBoxData->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QPushButton* btns = new QPushButton("Send");
    layBoxData->addWidget(btns);
    connect(btns, &QPushButton::clicked, this, &SProtPure::sendData);


    QGroupBox* groupBoxDataSec = new QGroupBox("Data sections");
    mainLay->addWidget(groupBoxDataSec);
    QVBoxLayout* dataSMainLay = new QVBoxLayout(groupBoxDataSec);


    QHBoxLayout* layBoxDataS0 = new QHBoxLayout();
    dataSMainLay->addLayout(layBoxDataS0);

    lab = new QLabel("Data:");
    layBoxDataS0->addWidget(lab);

    ledatas = new QLineEdit("FF");
    ledatas->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ledatas->setValidator(new HexValidator(1, 20, ledata));
    layBoxDataS0->addWidget(ledatas);


    QHBoxLayout* layBoxDataS = new QHBoxLayout();
    dataSMainLay->addLayout(layBoxDataS);

    lab = new QLabel("Number:");
    layBoxDataS->addWidget(lab);

    lesecnr = new QLineEdit("FF");
    lesecnr->setMaximumWidth(50);
    lesecnr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lesecnr->setValidator(new HexValidator(1, 1, lesecnr));
    layBoxDataS->addWidget(lesecnr);

    lab = new QLabel("offset:");
    layBoxDataS->addWidget(lab);

    lesecoff = new QLineEdit("FF");
    lesecoff->setMaximumWidth(50);
    lesecoff->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lesecoff->setValidator(new HexValidator(2, 1, lesecoff));
    layBoxDataS->addWidget(lesecoff);

    layBoxDataS->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    btns = new QPushButton("Set Data");
    layBoxDataS->addWidget(btns);
    connect(btns, &QPushButton::clicked, this, &SProtPure::setSec);
    btns = new QPushButton("Get Data");
    layBoxDataS->addWidget(btns);
    connect(btns, &QPushButton::clicked, this, &SProtPure::getSec);


    QHBoxLayout* layhello = new QHBoxLayout();
    mainLay->addLayout(layhello);

    layhello->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    btns = new QPushButton("Hello");
    layhello->addWidget(btns);
    connect(btns, &QPushButton::clicked, this, [&](){emit WriteFrame(FrameSProt::hello());});


    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    restore();
}

void SProtPure::Connected()
{
//    dbgFrame->setEnabled(true);
//    calFrame->setEnabled(true);
}

void SProtPure::Disconnected()
{
//    dbgFrame->setEnabled(false);
//    calFrame->setEnabled(false);
}

void SProtPure::FrameReaded(QSharedPointer<Frame> frame)
{

}

void SProtPure::sendData()
{
    emit WriteFrame(QSharedPointer<Frame>(new FrameSProt(lecmd->text().toInt(nullptr, 16), SU::string2ByteArray(ledata->text()))));
}

void SProtPure::setSec()
{
    uint8_t nr = lesecnr->text().toInt(nullptr, 16);
    uint8_t offset = lesecoff->text().toInt(nullptr, 16);
    QByteArray payload = SU::string2ByteArray(ledatas->text());
    emit WriteFrame(FrameSProt::setSec(nr, offset, payload));
}

void SProtPure::getSec()
{
    uint8_t nr = lesecnr->text().toInt(nullptr, 16);
    uint8_t offset = lesecoff->text().toInt(nullptr, 16);
    emit WriteFrame(FrameSProt::getSec(nr, offset));
}
