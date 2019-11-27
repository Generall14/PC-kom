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
}

void SProtPure::restore()
{
    lecmd->setText(RestoreAsString("lecmd", "000"));
    ledata->setText(RestoreAsString("ledata", "61 62 63"));
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
//    emit WritePureData(SU::string2ByteArray(ledata->text()));
}
