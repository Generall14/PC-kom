#include "IF01.hpp"
#include <QLabel>
#include <QPushButton>

IF01::IF01(QFrame* parent):
    Restorable("IF01"),
    cParent(parent)
{
    Init();
}

IF01::~IF01()
{
    Store("leToAdr", leToAdr->text());
    Store("sbwiRDCONST", sbwiRDCONST->value());
}

void IF01::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    sbwiRDCONST->setValue(RestoreAsInt("sbwiRDCONST", 0));
}

void IF01::InitRest()
{
    const uint MIN_PB_W = 200;

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);
    QLabel* lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);

    QHBoxLayout* wiRDCONSTLay = new QHBoxLayout();
    mainLay->addLayout(wiRDCONSTLay);
    QPushButton* pb = new QPushButton("wiRDCONST");
    connect(pb, SIGNAL(clicked(bool)), this, SLOT(SendwiRDCONST()));
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiRDCONSTLay->addWidget(pb);
    wiRDCONSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Offset:");
    wiRDCONSTLay->addWidget(lab);
    sbwiRDCONST = new QSpinBox();
    sbwiRDCONST->setMaximum(0xFFFFF);
    sbwiRDCONST->setMinimum(0);
    wiRDCONSTLay->addWidget(sbwiRDCONST);
}

void IF01::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF01::SendwiRDCONST()
{

}
