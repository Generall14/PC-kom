#include "IF00.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"

IF00::IF00(QFrame* parent):
    Restorable("IF00"),
    cParent(parent)
{
    Init();
}

IF00::~IF00()
{
    Store("leToAdr", leToAdr->text());
    Store("leConnO", leConnO->text());
}

void IF00::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    leConnO->setText(RestoreAsString("leConnO", "FF"));
}

void IF00::InitRest()
{
    const uint MIN_PB_W = 150;

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);
    QLabel* lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);

    QHBoxLayout* wkpSTORELay = new QHBoxLayout();
    mainLay->addLayout(wkpSTORELay);
    QPushButton* pb = new QPushButton("wkpSTORE");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpSTORE());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpSTORELay->addWidget(pb);
    wkpSTORELay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpCONNECTLay = new QHBoxLayout();
    mainLay->addLayout(wkpCONNECTLay);
    pb = new QPushButton("wkpCONNECT");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECT());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpCONNECTLay->addWidget(pb);
    wkpCONNECTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpCONNECToLay = new QHBoxLayout();
    mainLay->addLayout(wkpCONNECToLay);
    pb = new QPushButton("wkpCONNECTo");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECTo(SU::string2ByteArray(leConnO->text())));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpCONNECToLay->addWidget(pb);
    wkpCONNECToLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Następnik:");
    wkpCONNECToLay->addWidget(lab);
    leConnO = new QLineEdit("FF");
    leConnO->setInputMask("HH");
    leConnO->setMaximumWidth(40);
    wkpCONNECToLay->addWidget(leConnO);

    QHBoxLayout* wkpBUILDLay = new QHBoxLayout();
    mainLay->addLayout(wkpBUILDLay);
    pb = new QPushButton("wkpBUILD");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILD());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpBUILDLay->addWidget(pb);
    wkpBUILDLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpBUILDoLay = new QHBoxLayout();
    mainLay->addLayout(wkpBUILDoLay);
    pb = new QPushButton("wkpBUILDo");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILDo());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpBUILDoLay->addWidget(pb);
    wkpBUILDoLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* wkpRESETLay = new QHBoxLayout();
    mainLay->addLayout(wkpRESETLay);
    pb = new QPushButton("wkpRESET");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpRESET());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wkpRESETLay->addWidget(pb);
    wkpRESETLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
}

void IF00::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF00::SendMessage(QByteArray arr)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, 0, arr));
    emit Send(QList<Confirm>(), m);
}
