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
    Store("cbForceDoseRateAAdr", cbForceDoseRateAAdr->isChecked());
    Store("sbMsAutoDoseRateA", sbMsAutoDoseRateA->value());
    Store("cbEnAutoDoseRateA", cbEnAutoDoseRateA->isChecked());
    Store("leAdrAutoDoseRateA", leAdrAutoDoseRateA->text());
    Store("cbAlarmStateDir", cbAlarmStateDir->isChecked());
    Store("cbAlarmStateSetE1", cbAlarmStateSetE1->isChecked());
    Store("cbAlarmStateSetE2", cbAlarmStateSetE2->isChecked());
    Store("cbAlarmStateSetE3", cbAlarmStateSetE3->isChecked());
    Store("cbAlarmStateSetTh1", cbAlarmStateSetTh1->value());
    Store("cbAlarmStateSetTh2", cbAlarmStateSetTh2->value());
    Store("cbAlarmStateSetTh3", cbAlarmStateSetTh3->value());
    Store("sbAlarmStateSetPod1", sbAlarmStateSetPod1->value());
    Store("sbAlarmStateSetPod2", sbAlarmStateSetPod2->value());
    Store("sbAlarmStateSetPod3", sbAlarmStateSetPod3->value());
    Store("sbAlarmStateSetPrze1", sbAlarmStateSetPrze1->value());
    Store("sbAlarmStateSetPrze2", sbAlarmStateSetPrze2->value());
    Store("sbAlarmStateSetPrze3", sbAlarmStateSetPrze3->value());
    Store("cbForceWyAlAdr", cbForceWyAlAdr->isChecked());
    Store("sbMsAutoWyAl", sbMsAutoWyAl->value());
    Store("cbEnAutoWyAl", cbEnAutoWyAl->isChecked());
    Store("leAdrAutoWyAl", leAdrAutoWyAl->text());
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
    cbForceDoseRateAAdr->setChecked(RestoreAsBool("cbForceDoseRateAAdr", false));
    sbMsAutoDoseRateA->setValue(RestoreAsInt("sbMsAutoDoseRateA", 100));
    cbEnAutoDoseRateA->setChecked(RestoreAsBool("cbEnAutoDoseRateA", false));
    leAdrAutoDoseRateA->setText(RestoreAsString("leAdrAutoDoseRateA", "3F"));
    cbAlarmStateDir->setChecked(RestoreAsBool("cbAlarmStateDir", true));
    cbAlarmStateSetE1->setChecked(RestoreAsBool("cbAlarmStateSetE1", true));
    cbAlarmStateSetE2->setChecked(RestoreAsBool("cbAlarmStateSetE2", true));
    cbAlarmStateSetE3->setChecked(RestoreAsBool("cbAlarmStateSetE3", true));
    cbAlarmStateSetTh1->setValue(RestoreAsFloat("cbAlarmStateSetTh1", 0.001));
    cbAlarmStateSetTh2->setValue(RestoreAsFloat("cbAlarmStateSetTh2", 0.01));
    cbAlarmStateSetTh3->setValue(RestoreAsFloat("cbAlarmStateSetTh3", 0.1));
    sbAlarmStateSetPod1->setValue(RestoreAsInt("sbAlarmStateSetPod1", 6));
    sbAlarmStateSetPod2->setValue(RestoreAsInt("sbAlarmStateSetPod2", 6));
    sbAlarmStateSetPod3->setValue(RestoreAsInt("sbAlarmStateSetPod3", 6));
    sbAlarmStateSetPrze1->setValue(RestoreAsInt("sbAlarmStateSetPrze1", 6));
    sbAlarmStateSetPrze2->setValue(RestoreAsInt("sbAlarmStateSetPrze2", 6));
    sbAlarmStateSetPrze3->setValue(RestoreAsInt("sbAlarmStateSetPrze3", 6));
    cbForceWyAlAdr->setChecked(RestoreAsBool("cbForceWyAlAdr", false));
    sbMsAutoWyAl->setValue(RestoreAsInt("sbMsAutoWyAl", 100));
    cbEnAutoWyAl->setChecked(RestoreAsBool("cbEnAutoWyAl", false));
    leAdrAutoWyAl->setText(RestoreAsString("leAdrAutoWyAl", "3F"));
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
    lab = new QLabel("Per. [x100 ms]:");
    drAuto->addWidget(lab);
    sbMsAutoDoseRate = new QSpinBox();
    sbMsAutoDoseRate->setMinimum(1);
    sbMsAutoDoseRate->setMaximum(0xFFFF);
    sbMsAutoDoseRate->setValue(100);
    drAuto->addWidget(sbMsAutoDoseRate);

    //=============================================================================================
    QGroupBox* mocDawkiAlarm = new QGroupBox("Alarm mocy dawki");
    mainLay->addWidget(mocDawkiAlarm);
    QVBoxLayout* mdaLay = new QVBoxLayout(mocDawkiAlarm);
    mdaLay->setMargin(2);

    QHBoxLayout* draRead = new QHBoxLayout();
    mdaLay->addLayout(draRead);
    pb = new QPushButton("Odczytaj");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ReadAlarmState());});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    draRead->addWidget(pb);
    draRead->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    labAlarmState = new QLabel("-");
    draRead->addWidget(labAlarmState);

    QHBoxLayout* draKierunek = new QHBoxLayout();
    mdaLay->addLayout(draKierunek);
    pb = new QPushButton("Ustaw kierunek");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAlarmStateDir(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                cbAlarmStateDir->isChecked()), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    draKierunek->addWidget(pb);
    draKierunek->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbAlarmStateDir = new QCheckBox("Niebezpieczne wyższe wartości");
    draKierunek->addWidget(cbAlarmStateDir);

    QString ttthr = "Wartość progowa [Sv/h]";
    QString ttpod = "Podtrzymanie [x500 ms]";
    QString ttprz = "Przetrzymanie [x500 ms]";

    QHBoxLayout* draUstaw1 = new QHBoxLayout();
    mdaLay->addLayout(draUstaw1);
    pb = new QPushButton("Set UWAG.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAlarmStateUwag(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                cbAlarmStateSetE1->isChecked(),
                                                                cbAlarmStateSetTh1->value(),
                                                                sbAlarmStateSetPrze1->value(),
                                                                sbAlarmStateSetPod1->value()), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    draUstaw1->addWidget(pb);
    draUstaw1->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbAlarmStateSetE1 = new QCheckBox("En");
    draUstaw1->addWidget(cbAlarmStateSetE1);
    cbAlarmStateSetTh1 = new QDoubleSpinBox();
    draUstaw1->addWidget(cbAlarmStateSetTh1);
    cbAlarmStateSetTh1->setMaximumWidth(80);
    cbAlarmStateSetTh1->setMinimumWidth(80);
    cbAlarmStateSetTh1->setToolTip(ttthr);
    cbAlarmStateSetTh1->setDecimals(6);
    sbAlarmStateSetPod1 = new QSpinBox();
    draUstaw1->addWidget(sbAlarmStateSetPod1);
    sbAlarmStateSetPod1->setMaximumWidth(50);
    sbAlarmStateSetPod1->setMinimumWidth(50);
    sbAlarmStateSetPod1->setMinimum(0);
    sbAlarmStateSetPod1->setMaximum(0xff);
    sbAlarmStateSetPod1->setToolTip(ttpod);
    sbAlarmStateSetPrze1 = new QSpinBox();
    draUstaw1->addWidget(sbAlarmStateSetPrze1);
    sbAlarmStateSetPrze1->setMaximumWidth(50);
    sbAlarmStateSetPrze1->setMinimumWidth(50);
    sbAlarmStateSetPrze1->setMinimum(0);
    sbAlarmStateSetPrze1->setMaximum(0xff);
    sbAlarmStateSetPrze1->setToolTip(ttprz);

    QHBoxLayout* draUstaw2 = new QHBoxLayout();
    mdaLay->addLayout(draUstaw2);
    pb = new QPushButton("Set NIEB.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAlarmStateNieb(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                cbAlarmStateSetE2->isChecked(),
                                                                cbAlarmStateSetTh2->value(),
                                                                sbAlarmStateSetPrze2->value(),
                                                                sbAlarmStateSetPod2->value()), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    draUstaw2->addWidget(pb);
    draUstaw2->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbAlarmStateSetE2 = new QCheckBox("En");
    draUstaw2->addWidget(cbAlarmStateSetE2);
    cbAlarmStateSetTh2 = new QDoubleSpinBox();
    draUstaw2->addWidget(cbAlarmStateSetTh2);
    cbAlarmStateSetTh2->setMaximumWidth(80);
    cbAlarmStateSetTh2->setMinimumWidth(80);
    cbAlarmStateSetTh2->setToolTip(ttthr);
    cbAlarmStateSetTh2->setDecimals(6);
    sbAlarmStateSetPod2 = new QSpinBox();
    draUstaw2->addWidget(sbAlarmStateSetPod2);
    sbAlarmStateSetPod2->setMaximumWidth(50);
    sbAlarmStateSetPod2->setMinimumWidth(50);
    sbAlarmStateSetPod2->setMinimum(0);
    sbAlarmStateSetPod2->setMaximum(0xff);
    sbAlarmStateSetPod2->setToolTip(ttpod);
    sbAlarmStateSetPrze2 = new QSpinBox();
    draUstaw2->addWidget(sbAlarmStateSetPrze2);
    sbAlarmStateSetPrze2->setMaximumWidth(50);
    sbAlarmStateSetPrze2->setMinimumWidth(50);
    sbAlarmStateSetPrze2->setMinimum(0);
    sbAlarmStateSetPrze2->setMaximum(0xff);
    sbAlarmStateSetPrze2->setToolTip(ttprz);

    QHBoxLayout* draUstaw3 = new QHBoxLayout();
    mdaLay->addLayout(draUstaw3);
    pb = new QPushButton("Set ZAGR.");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAlarmStateZagr(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                cbAlarmStateSetE3->isChecked(),
                                                                cbAlarmStateSetTh3->value(),
                                                                sbAlarmStateSetPrze3->value(),
                                                                sbAlarmStateSetPod3->value()), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    draUstaw3->addWidget(pb);
    draUstaw3->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbAlarmStateSetE3 = new QCheckBox("En");
    draUstaw3->addWidget(cbAlarmStateSetE3);
    cbAlarmStateSetTh3 = new QDoubleSpinBox();
    draUstaw3->addWidget(cbAlarmStateSetTh3);
    cbAlarmStateSetTh3->setMaximumWidth(80);
    cbAlarmStateSetTh3->setMinimumWidth(80);
    cbAlarmStateSetTh3->setToolTip(ttthr);
    cbAlarmStateSetTh3->setDecimals(6);
    sbAlarmStateSetPod3 = new QSpinBox();
    draUstaw3->addWidget(sbAlarmStateSetPod3);
    sbAlarmStateSetPod3->setMaximumWidth(50);
    sbAlarmStateSetPod3->setMinimumWidth(50);
    sbAlarmStateSetPod3->setMinimum(0);
    sbAlarmStateSetPod3->setMaximum(0xff);
    sbAlarmStateSetPod3->setToolTip(ttpod);
    sbAlarmStateSetPrze3 = new QSpinBox();
    draUstaw3->addWidget(sbAlarmStateSetPrze3);
    sbAlarmStateSetPrze3->setMaximumWidth(50);
    sbAlarmStateSetPrze3->setMinimumWidth(50);
    sbAlarmStateSetPrze3->setMinimum(0);
    sbAlarmStateSetPrze3->setMaximum(0xff);
    sbAlarmStateSetPrze3->setToolTip(ttprz);


    QHBoxLayout* draForce = new QHBoxLayout();
    mdaLay->addLayout(draForce);
    pb = new QPushButton("Force");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceAlarmState(cbForceDoseRateAAdr->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    draForce->addWidget(pb);
    draForce->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbForceDoseRateAAdr = new QCheckBox("Do adresata");
    draForce->addWidget(cbForceDoseRateAAdr);

    QHBoxLayout* darAuto = new QHBoxLayout();
    mdaLay->addLayout(darAuto);
    pb = new QPushButton("Set auto");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAutoAlarmState(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                sbMsAutoDoseRateA->value(),
                                                                cbEnAutoDoseRateA->isChecked(),
                                                                leAdrAutoDoseRateA->text().toInt(nullptr, 16)), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    darAuto->addWidget(pb);
    darAuto->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbEnAutoDoseRateA = new QCheckBox("En");
    darAuto->addWidget(cbEnAutoDoseRateA);
    lab = new QLabel("Adr:");
    darAuto->addWidget(lab);
    leAdrAutoDoseRateA = new QLineEdit("FF");
    leAdrAutoDoseRateA->setInputMask("HH");
    leAdrAutoDoseRateA->setMaximumWidth(40);
    darAuto->addWidget(leAdrAutoDoseRateA);
    lab = new QLabel("Per. [x100 ms]:");
    darAuto->addWidget(lab);
    sbMsAutoDoseRateA = new QSpinBox();
    sbMsAutoDoseRateA->setMinimum(1);
    sbMsAutoDoseRateA->setMaximum(0xFFFF);
    sbMsAutoDoseRateA->setValue(100);
    darAuto->addWidget(sbMsAutoDoseRateA);

    //=============================================================================================
    QGroupBox* wyjsciaAlarmowe = new QGroupBox("Wyjścia alarmowe");
    mainLay->addWidget(wyjsciaAlarmowe);
    QVBoxLayout* wyaLay = new QVBoxLayout(wyjsciaAlarmowe);
    wyaLay->setMargin(2);

    QHBoxLayout* wyaForce = new QHBoxLayout();
    wyaLay->addLayout(wyaForce);
    pb = new QPushButton("Force");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceWyAlarm(cbForceWyAlAdr->isChecked()));});
    pb->setMaximumWidth(MIN_PB_W);
    pb->setMinimumWidth(MIN_PB_W);
    wyaForce->addWidget(pb);
    wyaForce->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbForceWyAlAdr = new QCheckBox("Do adresata");
    wyaForce->addWidget(cbForceWyAlAdr);

    QHBoxLayout* wyaAuto = new QHBoxLayout();
    wyaLay->addLayout(wyaAuto);
    pb = new QPushButton("Set auto");
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3SetAutoWyAlarm(
                                                                leMagic->text().toInt(nullptr, 16),
                                                                sbMsAutoWyAl->value(),
                                                                cbEnAutoWyAl->isChecked(),
                                                                leAdrAutoWyAl->text().toInt(nullptr, 16)), 1);});
    pb->setMaximumWidth(MIN_PB_W);
    wyaAuto->addWidget(pb);
    wyaAuto->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    cbEnAutoWyAl = new QCheckBox("En");
    wyaAuto->addWidget(cbEnAutoWyAl);
    lab = new QLabel("Adr:");
    wyaAuto->addWidget(lab);
    leAdrAutoWyAl = new QLineEdit("FF");
    leAdrAutoWyAl->setInputMask("HH");
    leAdrAutoWyAl->setMaximumWidth(40);
    wyaAuto->addWidget(leAdrAutoWyAl);
    lab = new QLabel("Per. [x100 ms]:");
    wyaAuto->addWidget(lab);
    sbMsAutoWyAl = new QSpinBox();
    sbMsAutoWyAl->setMinimum(1);
    sbMsAutoWyAl->setMaximum(0xFFFF);
    sbMsAutoWyAl->setValue(100);
    wyaAuto->addWidget(sbMsAutoWyAl);

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
    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessageZR3::zr3ForceDose(cbForceDoseAdr->isChecked()));});
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
    lab = new QLabel("Per. [x100 ms]:");
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
    lab = new QLabel("Per. [x100 ms]:");
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
        else if((mm.at(0)==0x30))
        {
            labAlarmState->setText("Bezpiecznie");
        }
        else if((mm.at(0)==0x31))
        {
            labAlarmState->setText("UWAGA");
        }
        else if((mm.at(0)==0x32))
        {
            labAlarmState->setText("NIEBEZPIECZENSTWO");
        }
        else if((mm.at(0)==0x33))
        {
            labAlarmState->setText("ZAGROZENIE ZYCIA!!!");
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
