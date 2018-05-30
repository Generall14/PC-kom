#include "IF00.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"

IF00::IF00(QFrame* parent):
    IFPanel(parent, "IF00base"),
    Restorable("IF00")
{
    Init();
}

IF00::~IF00()
{
    Store("leConnO", leConnO->text());
}

void IF00::LoadConfigs()
{
    leConnO->setText(RestoreAsString("leConnO", "FF"));
}

void IF00::InitRest()
{
    QHBoxLayout* wkpSTORELay = new QHBoxLayout();
    mainLay->addLayout(wkpSTORELay);
    QPushButton* pb = new QPushButton("wkpSTORE");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpSTORE(), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpSTORELay->addWidget(pb);
    wkpSTORELay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpCONNECTLay = new QHBoxLayout();
    mainLay->addLayout(wkpCONNECTLay);
    pb = new QPushButton("wkpCONNECT");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECT(), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpCONNECTLay->addWidget(pb);
    wkpCONNECTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpCONNECToLay = new QHBoxLayout();
    mainLay->addLayout(wkpCONNECToLay);
    pb = new QPushButton("wkpCONNECTo");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECTo(SU::string2ByteArray(leConnO->text())), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpCONNECToLay->addWidget(pb);
    wkpCONNECToLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QLabel* lab = new QLabel("Następnik:");
    wkpCONNECToLay->addWidget(lab);
    leConnO = new QLineEdit("FF");
    leConnO->setInputMask("HH");
    leConnO->setMaximumWidth(40);
    wkpCONNECToLay->addWidget(leConnO);

    QHBoxLayout* wkpBUILDLay = new QHBoxLayout();
    mainLay->addLayout(wkpBUILDLay);
    pb = new QPushButton("wkpBUILD");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILD(), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpBUILDLay->addWidget(pb);
    wkpBUILDLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpBUILDoLay = new QHBoxLayout();
    mainLay->addLayout(wkpBUILDoLay);
    pb = new QPushButton("wkpBUILDo");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILDo(), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpBUILDoLay->addWidget(pb);
    wkpBUILDoLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpRESETLay = new QHBoxLayout();
    mainLay->addLayout(wkpRESETLay);
    pb = new QPushButton("wkpRESET");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpRESET(), 0);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpRESETLay->addWidget(pb);
    wkpRESETLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
}

void IF00::Init()
{
    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}
