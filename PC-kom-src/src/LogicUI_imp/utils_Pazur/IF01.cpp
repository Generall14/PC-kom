#include "IF01.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"

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
    Store("sbwiRDSECTION", sbwiRDSECTION->value());
    Store("cbwiRDSECTION", cbwiRDSECTION->isChecked());
    Store("sbwiWRSECTION", sbwiWRSECTION->value());
    Store("cbwiWRSECTION", cbwiWRSECTION->isChecked());
    Store("lewiWRSECTION", lewiWRSECTION->text());
    Store("lewiWRSECTIONmagic", lewiWRSECTIONmagic->text());
}

void IF01::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    sbwiRDCONST->setValue(RestoreAsInt("sbwiRDCONST", 0));
    sbwiRDSECTION->setValue(RestoreAsInt("sbwiRDSECTION", 0));
    cbwiRDSECTION->setChecked(RestoreAsInt("cbwiRDSECTION", false));
    sbwiWRSECTION->setValue(RestoreAsInt("sbwiWRSECTION", 0));
    cbwiWRSECTION->setChecked(RestoreAsBool("cbwiWRSECTION", false));
    lewiWRSECTION->setText(RestoreAsString("lewiWRSECTION", ""));
    lewiWRSECTIONmagic->setText(RestoreAsString("lewiWRSECTIONmagic", "0000"));
}

void IF01::InitRest()
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

    QHBoxLayout* wiRDCONSTLay = new QHBoxLayout();
    mainLay->addLayout(wiRDCONSTLay);
    QPushButton* pb = new QPushButton("wiRDCONST");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wiRDCONST(sbwiRDCONST->value()));});
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

    QHBoxLayout* wiRDSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(wiRDSECTIONLay);
    pb = new QPushButton("wiRDSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRDSECTION_dev(sbwiRDSECTION->value(), cbwiRDSECTION->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiRDSECTIONLay->addWidget(pb);
    wiRDSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbwiRDSECTION = new QCheckBox("Prot");
    wiRDSECTIONLay->addWidget(cbwiRDSECTION);
    lab = new QLabel("Nr:");
    wiRDSECTIONLay->addWidget(lab);
    sbwiRDSECTION = new QSpinBox();
    sbwiRDSECTION->setMaximum(0x3F);
    sbwiRDSECTION->setMinimum(0);
    wiRDSECTIONLay->addWidget(sbwiRDSECTION);

    QHBoxLayout* wiWRSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(wiWRSECTIONLay);
    pb = new QPushButton("wiWRSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiWRSECTION_dev(sbwiWRSECTION->value(), cbwiWRSECTION->isChecked(),
                    lewiWRSECTIONmagic->text().toInt(nullptr, 16),
                    SU::string2ByteArray(lewiWRSECTION->text())));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiWRSECTIONLay->addWidget(pb);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Magic:");
    wiWRSECTIONLay->addWidget(lab);
    lewiWRSECTIONmagic = new QLineEdit();
    lewiWRSECTIONmagic->setValidator(new HexValidator(2, 1, lewiWRSECTIONmagic));
    lewiWRSECTIONmagic->setMaximumWidth(50);
    wiWRSECTIONLay->addWidget(lewiWRSECTIONmagic);
    cbwiWRSECTION = new QCheckBox("Prot");
    wiWRSECTIONLay->addWidget(cbwiWRSECTION);
    lab = new QLabel("Nr:");
    wiWRSECTIONLay->addWidget(lab);
    sbwiWRSECTION = new QSpinBox();
    sbwiWRSECTION->setMaximum(0x3F);
    sbwiWRSECTION->setMinimum(0);
    wiWRSECTIONLay->addWidget(sbwiWRSECTION);
    lewiWRSECTION = new QLineEdit("fe");
    lewiWRSECTION->setValidator(new HexValidator(1, 0, lewiWRSECTION));
    mainLay->addWidget(lewiWRSECTION);
}

void IF01::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF01::SendMessage(QByteArray arr)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, 1, arr));
    emit Send(QList<Confirm>(), m);
}
