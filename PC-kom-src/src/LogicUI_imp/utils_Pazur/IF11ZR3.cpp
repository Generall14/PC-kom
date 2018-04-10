#include "IF11ZR3.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"

IF11ZR3::IF11ZR3(QFrame* parent):
    Restorable("IF11ZR3"),
    cParent(parent)
{
    Init();
}

IF11ZR3::~IF11ZR3()
{
    Store("leToAdr", leToAdr->text());
    Store("letechREQmagic", letechREQmagic->text());
    Store("letechACCmagic", letechACCmagic->text());
    Store("letechACCrnd", letechACCrnd->text());
}

void IF11ZR3::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    letechREQmagic->setText(RestoreAsString("letechREQmagic", "1234"));
    letechACCmagic->setText(RestoreAsString("letechACCmagic", "1234"));
    letechACCrnd->setText(RestoreAsString("letechACCrnd", "1234"));
}

void IF11ZR3::InitRest()
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

//    QHBoxLayout* wiRDCONSTLay = new QHBoxLayout();
//    mainLay->addLayout(wiRDCONSTLay);
//    QPushButton* pb = new QPushButton("wiRDCONST");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wiRDCONST(sbwiRDCONST->value()));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wiRDCONSTLay->addWidget(pb);
//    wiRDCONSTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Offset:");
//    wiRDCONSTLay->addWidget(lab);
//    sbwiRDCONST = new QSpinBox();
//    sbwiRDCONST->setMaximum(0xFFFFF);
//    sbwiRDCONST->setMinimum(0);
//    wiRDCONSTLay->addWidget(sbwiRDCONST);

//    QHBoxLayout* wiRDSECTIONLay = new QHBoxLayout();
//    mainLay->addLayout(wiRDSECTIONLay);
//    pb = new QPushButton("wiRDSECTION(dev)");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiRDSECTION_dev(sbwiRDSECTION->value(), cbwiRDSECTION->isChecked()));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wiRDSECTIONLay->addWidget(pb);
//    wiRDSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    cbwiRDSECTION = new QCheckBox("Prot");
//    wiRDSECTIONLay->addWidget(cbwiRDSECTION);
//    lab = new QLabel("Nr:");
//    wiRDSECTIONLay->addWidget(lab);
//    sbwiRDSECTION = new QSpinBox();
//    sbwiRDSECTION->setMaximum(0x3F);
//    sbwiRDSECTION->setMinimum(0);
//    wiRDSECTIONLay->addWidget(sbwiRDSECTION);

//    QHBoxLayout* wiRDSECTIONLay2 = new QHBoxLayout();
//    mainLay->addLayout(wiRDSECTIONLay2);
//    pb = new QPushButton("wiRDSECTION(long)");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiRDSECTION_long(SU::string2ByteArray(lewiRDSECTION->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wiRDSECTIONLay2->addWidget(pb);
//    wiRDSECTIONLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Nr:");
//    wiRDSECTIONLay2->addWidget(lab);
//    lewiRDSECTION = new QLineEdit();
//    lewiRDSECTION->setValidator(new HexValidator(1, 5, lewiWRSECTIONmagic));
//    lewiRDSECTION->setMaximumWidth(150);
//    wiRDSECTIONLay2->addWidget(lewiRDSECTION);

//    QHBoxLayout* wiGFDALay = new QHBoxLayout();
//    mainLay->addLayout(wiGFDALay);
//    pb = new QPushButton("wiGFDA");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiGFDA(cbwiGFDA->isChecked(), SU::string2ByteArray(lewiGFDA->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wiGFDALay->addWidget(pb);
//    wiGFDALay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    cbwiGFDA = new QCheckBox("UTKAK");
//    wiGFDALay->addWidget(cbwiGFDA);
//    lab = new QLabel("Nr:");
//    wiGFDALay->addWidget(lab);
//    lewiGFDA = new QLineEdit();
//    lewiGFDA->setValidator(new HexValidator(1, 5, lewiWRSECTIONmagic));
//    lewiGFDA->setMaximumWidth(150);
//    wiGFDALay->addWidget(lewiGFDA);

    QHBoxLayout* techREQLay = new QHBoxLayout();
    mainLay->addLayout(techREQLay);
    QPushButton* pb = new QPushButton("techREQ");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::techREQ(letechREQmagic->text().toInt(nullptr, 16)));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techREQLay->addWidget(pb);
    techREQLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Magic:");
    techREQLay->addWidget(lab);
    letechREQmagic = new QLineEdit();
    letechREQmagic->setValidator(new HexValidator(2, 1, letechREQmagic));
    letechREQmagic->setMaximumWidth(50);
    techREQLay->addWidget(letechREQmagic);

    QHBoxLayout* techACCLay = new QHBoxLayout();
    mainLay->addLayout(techACCLay);
    pb = new QPushButton("techACC");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(
                    PureMessageZR3::techACC(letechACCmagic->text().toInt(nullptr, 16), letechACCrnd->text().toInt(nullptr, 16)));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    techACCLay->addWidget(pb);
    techACCLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Recieved rnd:");
    techACCLay->addWidget(lab);
    letechACCrnd = new QLineEdit();
    letechACCrnd->setValidator(new HexValidator(2, 1, letechACCrnd));
    letechACCrnd->setMaximumWidth(50);
    techACCLay->addWidget(letechACCrnd);
    lab = new QLabel("Magic:");
    techACCLay->addWidget(lab);
    letechACCmagic = new QLineEdit();
    letechACCmagic->setValidator(new HexValidator(2, 1, letechACCmagic));
    letechACCmagic->setMaximumWidth(50);
    techACCLay->addWidget(letechACCmagic);

//    QHBoxLayout* wiWRSECTIONLay2 = new QHBoxLayout();
//    mainLay->addLayout(wiWRSECTIONLay2);
//    pb = new QPushButton("wiWRSECTION(long)");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(SU::string2ByteArray(lewiWRSECTIONnr2->text()),
//                    lewiWRSECTIONmagic2->text().toInt(nullptr, 16),
//                    SU::string2ByteArray(lewiWRSECTION2->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wiWRSECTIONLay2->addWidget(pb);
//    wiWRSECTIONLay2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Magic:");
//    wiWRSECTIONLay2->addWidget(lab);
//    lewiWRSECTIONmagic2 = new QLineEdit();
//    lewiWRSECTIONmagic2->setValidator(new HexValidator(2, 1, lewiWRSECTIONmagic2));
//    lewiWRSECTIONmagic2->setMaximumWidth(50);
//    wiWRSECTIONLay2->addWidget(lewiWRSECTIONmagic2);
//    lab = new QLabel("Nr:");
//    wiWRSECTIONLay2->addWidget(lab);
//    lewiWRSECTIONnr2 = new QLineEdit();
//    lewiWRSECTIONnr2->setValidator(new HexValidator(1, 5, lewiWRSECTIONmagic));
//    lewiWRSECTIONnr2->setMaximumWidth(150);
//    wiWRSECTIONLay2->addWidget(lewiWRSECTIONnr2);
//    lewiWRSECTION2 = new QLineEdit("fe");
//    lewiWRSECTION2->setValidator(new HexValidator(1, 0, lewiWRSECTION2));
//    mainLay->addWidget(lewiWRSECTION2);
}

void IF11ZR3::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF11ZR3::SendMessage(QByteArray arr)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, 3, arr));
    emit Send(QList<Confirm>(), m);
}

void IF11ZR3::internalFrameReaded(QSharedPointer<Frame> fr)
{
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        if(msg.toPureData().at(2)==0x01)
        {
            letechACCrnd->setText(QString("%1%2").arg((uint)msg.toPureData().at(4)&0xFF, 2, 16, QChar('0'))
                                  .arg((uint)msg.toPureData().at(3)&0xFF, 2, 16, QChar('0')).toUpper());
            return;
        }
    }
}
