#include "IF01.hpp"
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <qDebug>
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
    Store("leSpAdr", leSpAdr->text());
    Store("leSpNAdr", leSpNAdr->text());
    Store("sbSpOTOPG", sbSpOTOPG->value());
    Store("cbSpBOCW", cbSpBOCW->isChecked());
    Store("cbSpBOPG", cbSpBOPG->isChecked());
    Store("cbSpBSPPG", cbSpBSPPG->isChecked());
    Store("cbSpBMP", cbSpBMP->isChecked());
    Store("cbSpBARP", cbSpBARP->isChecked());
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
    leSpAdr->setText(RestoreAsString("leSpAdr", "3F"));
    leSpNAdr->setText(RestoreAsString("leSpNAdr", "3F"));
    sbSpOTOPG->setValue(RestoreAsInt("sbSpOTOPG", 100));
    cbSpBOCW->setChecked(RestoreAsBool("cbSpBOCW", false));
    cbSpBOPG->setChecked(RestoreAsBool("cbSpBOPG", false));
    cbSpBSPPG->setChecked(RestoreAsBool("cbSpBSPPG", false));
    cbSpBMP->setChecked(RestoreAsBool("cbSpBMP", false));
    cbSpBARP->setChecked(RestoreAsBool("cbSpBARP", false));
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

    //========================= spec ===============================================================
    uint specs = MIN_PB_W/2;

    QGroupBox* gb = new QGroupBox("Adres urządzenia");
    mainLay->addWidget(gb);
    QHBoxLayout* hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    leSpAdr = new QLineEdit("3F");
    leSpAdr->setInputMask("HH");
    leSpAdr->setMaximumWidth(40);
    hl->addWidget(leSpAdr);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpAdr = new QLabel("??");
    labSpAdr->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpAdr);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdAU(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Adres następnika");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    leSpNAdr = new QLineEdit("3F");
    leSpNAdr->setInputMask("HH");
    leSpNAdr->setMaximumWidth(40);
    hl->addWidget(leSpNAdr);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpNAdr = new QLabel("??");
    labSpNAdr->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpNAdr);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdANWP(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Oczekiwane tempo otrzymywania głosu");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    sbSpOTOPG = new QSpinBox();
    sbSpOTOPG->setMinimum(0);
    sbSpOTOPG->setMaximum(0x7FF);
    hl->addWidget(sbSpOTOPG);
    lab = new QLabel("ms");
    hl->addWidget(lab);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpOTOPG = new QLabel("??");
    labSpOTOPG->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpOTOPG);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdOTOPG(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Blokada okna włączenia");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    cbSpBOCW = new QCheckBox("En");
    hl->addWidget(cbSpBOCW);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpBOCW = new QLabel("??");
    labSpBOCW->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpBOCW);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdBOCW(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Blokada odzyskiwania prawa głosu");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    cbSpBOPG = new QCheckBox("En");
    hl->addWidget(cbSpBOPG);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpBOPG = new QLabel("??");
    labSpBOPG->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpBOPG);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdBOPG(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Blokada sprawdzania przekazania głosu");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    cbSpBSPPG = new QCheckBox("En");
    hl->addWidget(cbSpBSPPG);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpBSPPG = new QLabel("??");
    labSpBSPPG->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpBSPPG);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdBSPPG(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Blokada mechanizmu potwierdzeń");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    cbSpBMP = new QCheckBox("En");
    hl->addWidget(cbSpBMP);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpBMP = new QLabel("??");
    labSpBMP->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpBMP);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdBMP(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);

    gb = new QGroupBox("Blokada algorytmów restrukturyzacji");
    mainLay->addWidget(gb);
    hl = new QHBoxLayout();
    gb->setLayout(hl);
    pb = new QPushButton("Zapisz");
//    connect(pb, &QPushButton::clicked, [this](){
//        SendMessage(PureMessage::wiWRSECTION_long(
//                        leMagic->text().toInt(nullptr, 16),
//                        SU::string2ByteArray(lewiWRSECTION2->text())
//                        ), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
    cbSpBARP = new QCheckBox("En");
    hl->addWidget(cbSpBARP);
    wiWRSECTIONLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labSpBARP = new QLabel("??");
    labSpBARP->setAlignment(Qt::AlignRight);
    hl->addWidget(labSpBARP);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){
        SendMessage(PureMessage::wiRdBARP(), 1);});
    pb->setMaximumWidth(specs);
    pb->setMinimumWidth(specs);
    hl->addWidget(pb);
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
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        QString lock = "ZABLOKOWANO", unlock = "odblokowano";
        if((msg.toPureData().at(0)&0xC0)==0x40) // ifs = 1
        {
            QByteArray mm = msg.toPureData().mid(2);
            if((mm.at(0)==0x03)&&((uchar)mm.at(1)==0x80)&&((uchar)mm.at(2)==0x80)&&((uchar)mm.at(3)==0x80)&&((uchar)mm.at(4)==0x80))
            {
                if(mm.size()<7)
                    return;
                if((uchar)mm.at(5)==0xc0)
                    labSpAdr->setText(QString("0x%1").arg(mm.at(6)&0x3F, 2, 16, QChar('0')));
                else if((uchar)mm.at(5)==0xc1)
                    labSpNAdr->setText(QString("0x%1").arg(mm.at(6)&0x3F, 2, 16, QChar('0')));
                else if((uchar)mm.at(5)==0xc2)
                {
                    if(mm.size()<7)
                        return;
                    uint tempo = 0;
                    tempo |= mm.at(6)&0xFF;
                    tempo |= (mm.at(7)<<8)&0x700;
                    labSpOTOPG->setText(QString("%1 ms").arg(tempo));
                }
                else if((uchar)mm.at(5)==0xc3)
                {
                    if(mm.at(6)&0x01)
                        labSpBOPG->setText(lock);
                    else
                        labSpBOPG->setText(unlock);
                }
                else if((uchar)mm.at(5)==0xc4)
                {
                    if(mm.at(6)&0x01)
                        labSpBOCW->setText(lock);
                    else
                        labSpBOCW->setText(unlock);
                }
                else if((uchar)mm.at(5)==0xc5)
                {
                    if(mm.at(6)&0x01)
                        labSpBSPPG->setText(lock);
                    else
                        labSpBSPPG->setText(unlock);
                }
                else if((uchar)mm.at(5)==0xc6)
                {
                    if(mm.at(6)&0x01)
                        labSpBMP->setText(lock);
                    else
                        labSpBMP->setText(unlock);
                }
                else if((uchar)mm.at(5)==0xca)
                {
                    if(mm.at(6)&0x01)
                        labSpBARP->setText(lock);
                    else
                        labSpBARP->setText(unlock);
                }
            }
        }
    }
}
