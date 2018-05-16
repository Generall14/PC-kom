#include "IF10ZR3s.hpp"
#include <QLabel>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/PureMessageZR3.hpp"
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"
#include <qdebug.h>
#include "Frame_imp/FramePazur.hpp"
#include <QGroupBox>

IF10ZR3s::IF10ZR3s(QFrame* parent):
    Restorable("IF10ZR3s"),
    cParent(parent)
{
    Init();
}

IF10ZR3s::~IF10ZR3s()
{
    Store("leToAdr", leToAdr->text());
    Store("dsbzr3SetDose", dsbzr3SetDose->value());
    Store("cbForceDoseRateAdr", cbForceDoseRateAdr->isChecked());
    Store("cbForceDoseAdr", cbForceDoseAdr->isChecked());
    Store("cbForceEstsAdr", cbForceEstsAdr->isChecked());
    Store("leMagic", leMagic->text());
    Store("cbEnAutoDoseRate", cbEnAutoDoseRate->isChecked());
    Store("leAdrAutoDoseRate", leAdrAutoDoseRate->text());
    Store("sbMsAutoDoseRate", sbMsAutoDoseRate->value());
    Store("cbEnAutoDose", cbEnAutoDose->isChecked());
    Store("leAdrAutoDose", leAdrAutoDose->text());
    Store("sbMsAutoDose", sbMsAutoDose->value());
    Store("cbEnAutoEst", cbEnAutoEst->isChecked());
    Store("leAdrAutoEst", leAdrAutoEst->text());
    Store("sbMsAutoEst", sbMsAutoEst->value());
}

void IF10ZR3s::LoadConfigs()
{
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    dsbzr3SetDose->setValue(RestoreAsFloat("dsbzr3SetDose", 0.0));
    cbForceDoseRateAdr->setChecked(RestoreAsBool("cbForceDoseRateAdr", false));
    cbForceDoseAdr->setChecked(RestoreAsBool("cbForceDoseAdr", false));
    cbForceEstsAdr->setChecked(RestoreAsBool("cbForceEstsAdr", false));
    leMagic->setText(RestoreAsString("leMagic", "0000"));
    cbEnAutoDoseRate->setChecked(RestoreAsBool("cbEnAutoDoseRate", false));
    leAdrAutoDoseRate->setText(RestoreAsString("leAdrAutoDoseRate", "3F"));
    sbMsAutoDoseRate->setValue(RestoreAsInt("sbMsAutoDoseRate", 100));
    cbEnAutoDose->setChecked(RestoreAsBool("cbEnAutoDose", "false"));
    leAdrAutoDose->setText(RestoreAsString("leAdrAutoDose", "3F"));
    sbMsAutoDose->setValue(RestoreAsInt("sbMsAutoDose", 100));
    cbEnAutoEst->setChecked(RestoreAsBool("cbEnAutoEst", "false"));
    leAdrAutoEst->setText(RestoreAsString("leAdrAutoEst", "3F"));
    sbMsAutoEst->setValue(RestoreAsInt("sbMsAutoEst", 100));
}

void IF10ZR3s::InitRest()
{
    const uint MIN_PB_W = 150;

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainLay->addLayout(toAdrLay);
    QLabel* lab = new QLabel("Magic:");
    toAdrLay->addWidget(lab);
    leMagic = new QLineEdit("0000");
    leMagic->setInputMask("HHHH");
    leMagic->setMaximumWidth(40);
    toAdrLay->addWidget(leMagic);
    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);

    //=============================================================================================
    QGroupBox* mocDawki = new QGroupBox("Pomiar/szacowanie mocy dawki");
    mainLay->addWidget(mocDawki);
    QVBoxLayout* mdLay = new QVBoxLayout(mocDawki);
    mdLay->setMargin(2);

    QHBoxLayout* drRead = new QHBoxLayout();
    mdLay->addLayout(drRead);
    QPushButton* pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDoseRate());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    drRead->addWidget(pb);
    drRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDoseRate = new QLabel("-");
    drRead->addWidget(labDoseRate);

    QHBoxLayout* drProbeRead = new QHBoxLayout();
    mdLay->addLayout(drProbeRead);
    pb = new QPushButton("Rst");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3RstDoseRateProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    drProbeRead->addWidget(pb);
    pb = new QPushButton("Próbka");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDoseRateProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    drProbeRead->addWidget(pb);
    drProbeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDoseRateProbe = new QLabel("-");
    drProbeRead->addWidget(labDoseRateProbe);

    QHBoxLayout* drForce = new QHBoxLayout();
    mdLay->addLayout(drForce);
    pb = new QPushButton("Force");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceDoseRate(cbForceDoseRateAdr->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    drForce->addWidget(pb);
    drForce->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbForceDoseRateAdr = new QCheckBox("Do adresata");
    drForce->addWidget(cbForceDoseRateAdr);

    QHBoxLayout* drAuto = new QHBoxLayout();
    mdLay->addLayout(drAuto);
    pb = new QPushButton("Set auto");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAutoDoseRate(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                sbMsAutoDoseRate->value(),
                                                                cbEnAutoDoseRate->isChecked(),
                                                                leAdrAutoDoseRate->text().toInt(nullptr, 16)), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    drAuto->addWidget(pb);
    drAuto->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbEnAutoDoseRate = new QCheckBox("En");
    drAuto->addWidget(cbEnAutoDoseRate);
    lab = new QLabel("Adr:");
    drAuto->addWidget(lab);
    leAdrAutoDoseRate = new QLineEdit("FF");
    leAdrAutoDoseRate->setInputMask("HH");
    leAdrAutoDoseRate->setMaximumWidth(40);
    drAuto->addWidget(leAdrAutoDoseRate);
    lab = new QLabel("Per. [ms]:");
    drAuto->addWidget(lab);
    sbMsAutoDoseRate = new QSpinBox();
    sbMsAutoDoseRate->setMinimum(1);
    sbMsAutoDoseRate->setMaximum(0xFFFF);
    sbMsAutoDoseRate->setValue(100);
    drAuto->addWidget(sbMsAutoDoseRate);

    //=============================================================================================
    QGroupBox* dawka = new QGroupBox("Pomiar/szacowanie dawki");
    mainLay->addWidget(dawka);
    QVBoxLayout* dLay = new QVBoxLayout(dawka);
    dLay->setMargin(2);

    QHBoxLayout* dRead = new QHBoxLayout();
    dLay->addLayout(dRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadDose());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    dRead->addWidget(pb);
    dRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labDose = new QLabel("-");
    dRead->addWidget(labDose);

    QHBoxLayout* dSet = new QHBoxLayout();
    dLay->addLayout(dSet);
    pb = new QPushButton("Ustaw");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetDose(dsbzr3SetDose->value()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    dSet->addWidget(pb);
    dSet->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    dsbzr3SetDose = new QDoubleSpinBox();
    dSet->addWidget(dsbzr3SetDose);
    dsbzr3SetDose->setMaximumWidth(120);
    dsbzr3SetDose->setMinimumWidth(120);
    dsbzr3SetDose->setDecimals(12);

    QHBoxLayout* dForce = new QHBoxLayout();
    dLay->addLayout(dForce);
    pb = new QPushButton("Force");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceDose(cbForceDoseRateAdr->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    dForce->addWidget(pb);
    dForce->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbForceDoseAdr = new QCheckBox("Do adresata");
    dForce->addWidget(cbForceDoseAdr);

    QHBoxLayout* dAuto = new QHBoxLayout();
    dLay->addLayout(dAuto);
    pb = new QPushButton("Set auto");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAutoDose(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                sbMsAutoDose->value(),
                                                                cbEnAutoDose->isChecked(),
                                                                leAdrAutoDose->text().toInt(nullptr, 16)), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    dAuto->addWidget(pb);
    dAuto->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbEnAutoDose = new QCheckBox("En");
    dAuto->addWidget(cbEnAutoDose);
    lab = new QLabel("Adr:");
    dAuto->addWidget(lab);
    leAdrAutoDose = new QLineEdit("FF");
    leAdrAutoDose->setInputMask("HH");
    leAdrAutoDose->setMaximumWidth(40);
    dAuto->addWidget(leAdrAutoDose);
    lab = new QLabel("Per. [ms]:");
    dAuto->addWidget(lab);
    sbMsAutoDose = new QSpinBox();
    sbMsAutoDose->setMinimum(1);
    sbMsAutoDose->setMaximum(0xFFFF);
    sbMsAutoDose->setValue(100);
    dAuto->addWidget(sbMsAutoDose);

    //=============================================================================================
    QGroupBox* ests = new QGroupBox("Estymaty");
    mainLay->addWidget(ests);
    QVBoxLayout* esLay = new QVBoxLayout(ests);
    esLay->setMargin(2);

    QHBoxLayout* estForce = new QHBoxLayout();
    esLay->addLayout(estForce);
    pb = new QPushButton("Force");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceEsts(cbForceEstsAdr->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    estForce->addWidget(pb);
    estForce->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbForceEstsAdr = new QCheckBox("Do adresata");
    estForce->addWidget(cbForceEstsAdr);

    QHBoxLayout* estAuto = new QHBoxLayout();
    esLay->addLayout(estAuto);
    pb = new QPushButton("Set auto");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAutoEst(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                sbMsAutoEst->value(),
                                                                cbEnAutoEst->isChecked(),
                                                                leAdrAutoEst->text().toInt(nullptr, 16)), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    estAuto->addWidget(pb);
    estAuto->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbEnAutoEst = new QCheckBox("En");
    estAuto->addWidget(cbEnAutoEst);
    lab = new QLabel("Adr:");
    estAuto->addWidget(lab);
    leAdrAutoEst = new QLineEdit("FF");
    leAdrAutoEst->setInputMask("HH");
    leAdrAutoEst->setMaximumWidth(40);
    estAuto->addWidget(leAdrAutoEst);
    lab = new QLabel("Per. [ms]:");
    estAuto->addWidget(lab);
    sbMsAutoEst = new QSpinBox();
    sbMsAutoEst->setMinimum(1);
    sbMsAutoEst->setMaximum(0xFFFF);
    sbMsAutoEst->setValue(100);
    estAuto->addWidget(sbMsAutoEst);

    //=============================================================================================
    QGroupBox* energia = new QGroupBox("(G) Szacowanie dominującej energii gamma");
    mainLay->addWidget(energia);
    QVBoxLayout* seLay = new QVBoxLayout(energia);
    seLay->setMargin(2);

    QHBoxLayout* eeRead = new QHBoxLayout();
    seLay->addLayout(eeRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedEnergy());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    eeRead->addWidget(pb);
    eeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedEnergy = new QLabel("-");
    eeRead->addWidget(labEstimatedEnergy);

    QHBoxLayout* eeProbeRead = new QHBoxLayout();
    seLay->addLayout(eeProbeRead);
    pb = new QPushButton("Rst");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3RstEstimatedEnergyProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    eeProbeRead->addWidget(pb);
    pb = new QPushButton("Próbka");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedEnergyProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    eeProbeRead->addWidget(pb);
    eeProbeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedEnergyProbe = new QLabel("-");
    eeProbeRead->addWidget(labEstimatedEnergyProbe);

    //=============================================================================================
    QGroupBox* estNeutron = new QGroupBox("(G) Szacowanie strumienia neutronow");
    mainLay->addWidget(estNeutron);
    QVBoxLayout* enLay = new QVBoxLayout(estNeutron);
    enLay->setMargin(2);

    QHBoxLayout* enRead = new QHBoxLayout();
    enLay->addLayout(enRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedNeutronB());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    enRead->addWidget(pb);
    enRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedNeutron = new QLabel("-");
    enRead->addWidget(labEstimatedNeutron);

    QHBoxLayout* snProbeRead = new QHBoxLayout();
    enLay->addLayout(snProbeRead);
    pb = new QPushButton("Rst");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3RstEstimatedNeutronBProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    snProbeRead->addWidget(pb);
    pb = new QPushButton("Próbka");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedNeutronBProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    snProbeRead->addWidget(pb);
    snProbeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedNeutronProbe = new QLabel("-");
    snProbeRead->addWidget(labEstimatedNeutronProbe);

    //=============================================================================================
    QGroupBox* estGamma = new QGroupBox("(N) Szacowanie mocy dawki gamma");
    mainLay->addWidget(estGamma);
    QVBoxLayout* egLay = new QVBoxLayout(estGamma);
    egLay->setMargin(2);

    QHBoxLayout* egRead = new QHBoxLayout();
    egLay->addLayout(egRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedGammaDoseRate());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    egRead->addWidget(pb);
    egRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedGammaDoseRate = new QLabel("-");
    egRead->addWidget(labEstimatedGammaDoseRate);

    QHBoxLayout* edrProbeRead = new QHBoxLayout();
    egLay->addLayout(edrProbeRead);
    pb = new QPushButton("Rst");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3RstEstimatedGammaDoseRateProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    edrProbeRead->addWidget(pb);
    pb = new QPushButton("Próbka");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadEstimatedGammaDoseRateProbe());});
    pb->setMaximumWidth(MIN_PB_W/2);
    pb->setMinimumWidth(MIN_PB_W/2);
    edrProbeRead->addWidget(pb);
    edrProbeRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labEstimatedGammaDoseRateProbe = new QLabel("-");
    edrProbeRead->addWidget(labEstimatedGammaDoseRateProbe);
}

void IF10ZR3s::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void IF10ZR3s::SendMessage(QByteArray arr, uint ifs)
{
    QList<Message> m;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    m.append(Message(to, ifs, arr));
    emit Send(QList<Confirm>(), m);
}

void IF10ZR3s::internalFrameReaded(QSharedPointer<Frame> fr)
{
    if(!(*fr).isValid())
        return;
    if(((*fr).pureData().at(0)&0x3F)!=(leToAdr->text().toInt(nullptr, 16)&0x3F))
        return;
    FramePazur paz(fr->pureData());
    for(auto msg: paz.getMessages().getMessages())
    {
        QByteArray mm = msg.toPureData().mid(2);
        if((mm.at(0)==0x20)&&(mm.at(1)==0x04))
        {
            if(mm.size()<11)
                return;
            labDose->setText(SU::displayFloat(SU::byteArray322Float32(mm.mid(2, 4)), 3)+"Sv");
        }
        else if((mm.at(0)==0x70))
        {
            labDoseRateProbe->setText(ReadMeasure(mm.mid(1), "Sv/h"));
        }
        else if((mm.at(0)==0x20)&&(mm.at(1)==0x02))
        {
            labDoseRate->setText(ReadMeasure(mm.mid(2), "Sv/h"));
        }
        else if((mm.at(0)==0x20)&&(mm.at(1)==0x15))
        {
            labEstimatedEnergy->setText(ReadMeasure(mm.mid(2), "eV"));
        }
        else if(((uchar)mm.at(0)==0xF0)&&(mm.at(1)==0x20))
        {
            labEstimatedEnergyProbe->setText(ReadMeasure(mm.mid(2), "eV"));
        }
        else if((mm.at(0)==0x20)&&(mm.at(1)==0x05))
        {
            labEstimatedNeutron->setText(ReadMeasure(mm.mid(2), "1/s/cm^2"));
        }
        else if(((uchar)mm.at(0)==0xF0)&&(mm.at(1)==0x40))
        {
            labEstimatedNeutronProbe->setText(ReadMeasure(mm.mid(2), "1/s/cm^2"));
        }
        else if(((uchar)mm.at(0)==0xA0)&&(mm.at(1)==0x20)&&(mm.at(2)==0x02))
        {
            labEstimatedGammaDoseRate->setText(ReadMeasure(mm.mid(3), "Sv/h"));
        }

        if(((uchar)mm.at(0)==0xF0)&&(mm.at(1)==0x20))
        {
            labEstimatedGammaDoseRateProbe->setText(ReadMeasure(mm.mid(2), "Sv/h"));
        }
    }
}

QString IF10ZR3s::ReadMeasure(QByteArray dat, QString unit)
{
    if(dat.size()<9)
        return "ERROR";
    QString text = SU::displayFloat(SU::byteArray322Float32(dat.mid(0, 4)), 3)+unit;
    text.append(QString(" +%1\% -%2\%")
                .arg(int(SU::byteArray2f5_11(dat.mid(4, 2))*100))
                .arg(int(SU::byteArray2f5_11(dat.mid(6, 2))*100))
                );
    if(dat.at(8)&0x01)
        text.append(" !DGZ!");
    if(dat.at(8)&0x02)
        text.append(" !GGZ!");
    return text;
}
