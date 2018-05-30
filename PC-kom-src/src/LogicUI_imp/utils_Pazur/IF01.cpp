#include "IF01.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessage.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"

IF01::IF01(QFrame* parent):
    IFPanel(parent, "IF01base"),
    Restorable("IF01")
{
    Init();
}

IF01::~IF01()
{
    Store("sbwiRDCONST", sbwiRDCONST->value());
    Store("sbwiRDSECTION", sbwiRDSECTION->value());
    Store("cbwiRDSECTION", cbwiRDSECTION->isChecked());
    Store("sbwiWRSECTION", sbwiWRSECTION->value());
    Store("cbwiWRSECTION", cbwiWRSECTION->isChecked());
    Store("lewiWRSECTION", lewiWRSECTION->text());
    Store("lewiRDSECTION", lewiRDSECTION->text());
    Store("lewiWRSECTIONnr2", lewiWRSECTIONnr2->text());
    Store("lewiWRSECTION2", lewiWRSECTION2->text());
    Store("cbwiGFDA", cbwiGFDA->isChecked());
    Store("lewiGFDA", lewiGFDA->text());
}

void IF01::LoadConfigs()
{
    sbwiRDCONST->setValue(RestoreAsInt("sbwiRDCONST", 0));
    sbwiRDSECTION->setValue(RestoreAsInt("sbwiRDSECTION", 0));
    cbwiRDSECTION->setChecked(RestoreAsBool("cbwiRDSECTION", false));
    sbwiWRSECTION->setValue(RestoreAsInt("sbwiWRSECTION", 0));
    cbwiWRSECTION->setChecked(RestoreAsBool("cbwiWRSECTION", false));
    lewiWRSECTION->setText(RestoreAsString("lewiWRSECTION", ""));
    lewiRDSECTION->setText(RestoreAsString("lewiRDSECTION", ""));
    lewiWRSECTIONnr2->setText(RestoreAsString("lewiWRSECTIONnr2", ""));
    lewiWRSECTION2->setText(RestoreAsString("lewiWRSECTION2", ""));
    cbwiGFDA->setChecked(RestoreAsBool("cbwiGFDA", false));
    lewiGFDA->setText(RestoreAsString("lewiGFDA", ""));
}

void IF01::InitRest()
{
    QHBoxLayout* wiRDCONSTLay = new QHBoxLayout();
    mainLay->addLayout(wiRDCONSTLay);
    QPushButton* pb = new QPushButton("wiRDCONST");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wiRDCONST(sbwiRDCONST->value()), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiRDCONSTLay->addWidget(pb);
    wiRDCONSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QLabel* lab = new QLabel("Offset:");
    wiRDCONSTLay->addWidget(lab);
    sbwiRDCONST = new QSpinBox();
    sbwiRDCONST->setMaximum(0xFFFFF);
    sbwiRDCONST->setMinimum(0);
    wiRDCONSTLay->addWidget(sbwiRDCONST);

    QHBoxLayout* wiRDSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(wiRDSECTIONLay);
    pb = new QPushButton("wiRDSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRDSECTION_dev(sbwiRDSECTION->value(), cbwiRDSECTION->isChecked()), 1);});
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

    QHBoxLayout* wiRDSECTIONLay2 = new QHBoxLayout();
    mainLay->addLayout(wiRDSECTIONLay2);
    pb = new QPushButton("wiRDSECTION(long)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRDSECTION_long(SU::string2ByteArray(lewiRDSECTION->text())), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiRDSECTIONLay2->addWidget(pb);
    wiRDSECTIONLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Nr:");
    wiRDSECTIONLay2->addWidget(lab);
    lewiRDSECTION = new QLineEdit();
    lewiRDSECTION->setValidator(new HexValidator(1, 8, lewiRDSECTION));
    lewiRDSECTION->setMaximumWidth(150);
    wiRDSECTIONLay2->addWidget(lewiRDSECTION);

    QHBoxLayout* wiGFDALay = new QHBoxLayout();
    mainLay->addLayout(wiGFDALay);
    pb = new QPushButton("wiGFDA");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiGFDA(cbwiGFDA->isChecked(), SU::string2ByteArray(lewiGFDA->text())), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiGFDALay->addWidget(pb);
    wiGFDALay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbwiGFDA = new QCheckBox("UTKAK");
    wiGFDALay->addWidget(cbwiGFDA);
    lab = new QLabel("Nr:");
    wiGFDALay->addWidget(lab);
    lewiGFDA = new QLineEdit();
    lewiGFDA->setValidator(new HexValidator(1, 8, lewiGFDA));
    lewiGFDA->setMaximumWidth(150);
    wiGFDALay->addWidget(lewiGFDA);

    QHBoxLayout* wiWRSECTIONLay = new QHBoxLayout();
    mainLay->addLayout(wiWRSECTIONLay);
    pb = new QPushButton("wiWRSECTION(dev)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiWRSECTION_dev(sbwiWRSECTION->value(), cbwiWRSECTION->isChecked(),
                    leMagic->text().toInt(nullptr, 16),
                    SU::string2ByteArray(lewiWRSECTION->text())), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiWRSECTIONLay->addWidget(pb);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
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

    QHBoxLayout* wiWRSECTIONLay2 = new QHBoxLayout();
    mainLay->addLayout(wiWRSECTIONLay2);
    pb = new QPushButton("wiWRSECTION(long)");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiWRSECTION_long(SU::string2ByteArray(lewiWRSECTIONnr2->text()),
                    leMagic->text().toInt(nullptr, 16),
                    SU::string2ByteArray(lewiWRSECTION2->text())), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wiWRSECTIONLay2->addWidget(pb);
    wiWRSECTIONLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Nr:");
    wiWRSECTIONLay2->addWidget(lab);
    lewiWRSECTIONnr2 = new QLineEdit();
    lewiWRSECTIONnr2->setValidator(new HexValidator(1, 8, lewiWRSECTIONnr2));
    lewiWRSECTIONnr2->setMaximumWidth(150);
    wiWRSECTIONLay2->addWidget(lewiWRSECTIONnr2);
    lewiWRSECTION2 = new QLineEdit("fe");
    lewiWRSECTION2->setValidator(new HexValidator(1, 0, lewiWRSECTION2));
    mainLay->addWidget(lewiWRSECTION2);
}

void IF01::Init()
{
    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF01::internalFrameReaded(QSharedPointer<Frame> fr)
{
    IFPanel::internalFrameReaded(fr);
    return;
//    if(!(*fr).isValid())
//        return;
//    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
//        return;
//    FramePazur paz(fr->pureData());
//    for(auto msg: paz.getMessages().getMessages())
//    {
//        if(msg.toPureData().at(2)==0x01)
//        {
//            letechACCrnd->setText(QString("%1%2").arg((uint)msg.toPureData().at(4)&0xFF, 2, 16, QChar('0'))
//                                  .arg((uint)msg.toPureData().at(3)&0xFF, 2, 16, QChar('0')).toUpper());
//            return;
//        }
//    }
}
