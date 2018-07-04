#include "KontrolerPomiarowy.hpp"
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include "Utils/ValidateHex.hpp"
#include "Utils/StaticUtils.hpp"

KontrolerPomiarowy::KontrolerPomiarowy(uint nr, QFrame* parent):
    QObject(parent),
    Restorable("KontrolerPomiarowy"+QString("%1").arg((uint)nr&0xFF, 2, 16, QChar('0')).toUpper()),
    cParent(parent),
    myAdr(nr)
{
    gnam.append("[010] x0.3"); gval.insertMulti(gnam.at(0), 0x02);
    gnam.append("[110] x0.6"); gval.insertMulti(gnam.at(1), 0x06);
    gnam.append("[000] x1.15"); gval.insertMulti(gnam.at(2), 0x00);
    gnam.append("[011] x2"); gval.insertMulti(gnam.at(3), 0x03);
    gnam.append("[111] x4"); gval.insertMulti(gnam.at(4), 0x07);
    gnam.append("[001] x7.5"); gval.insertMulti(gnam.at(5), 0x01);
    gnam.append("[101] x15"); gval.insertMulti(gnam.at(6), 0x05);

    Init();
}

KontrolerPomiarowy::~KontrolerPomiarowy()
{
//    Store("lekAdrLoc", lekAdrLoc->text());
    Store("ograniczenie", ograniczenie->isChecked());
    Store("leMaxHV", leMaxHV->text());
    Store("leHV", leHV->text());
    Store("kcbox", kcbox->currentIndex());
    Store("rozniczkowanie", rozniczkowanie->isChecked());
    Store("leOFFSET", leOFFSET->text());
    Store("leTRIGGER", leTRIGGER->text());
    Store("leKANALY", leKANALY->text());
}

void KontrolerPomiarowy::LoadConfigs()
{
//    lekAdrLoc->setText(RestoreAsString("lekAdrLoc", "FF"));
    ograniczenie->setChecked(RestoreAsBool("ograniczenie", true));
    leMaxHV->setText(RestoreAsString("leMaxHV", "C0"));
    leHV->setText(RestoreAsString("leHV", "00"));
    kcbox->setCurrentIndex(RestoreAsInt("kcbox", 0));
    rozniczkowanie->setChecked(RestoreAsBool("rozniczkowanie", false));
    leOFFSET->setText(RestoreAsString("leOFFSET", "0000"));
    leTRIGGER->setText(RestoreAsString("leTRIGGER", "0000"));
    leKANALY->setText(RestoreAsString("leKANALY", "0010 0020"));
}

void KontrolerPomiarowy::InitRest()
{
//    QHBoxLayout* groupBoxKonfiguracja23 = new QHBoxLayout();
//    mainLay->addLayout(groupBoxKonfiguracja23);
//    QLabel* tl23 = new QLabel("Wyślij na adres lokalny:");
//    groupBoxKonfiguracja23->addWidget(tl23);
//    lekAdrLoc = new QLineEdit("FF");
//    lekAdrLoc->setMaximumWidth(50);
//    lekAdrLoc->setToolTip("Docelowy adres lokalny komendy z konfiguracją szerokości kanałów.");
//    lekAdrLoc->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    lekAdrLoc->setValidator(new HexValidator(1, 1, lekAdrLoc));

//    groupBoxKonfiguracja23->addWidget(lekAdrLoc);

    QFrame* groupBoxHV = new QFrame();
    groupBoxHV->setFrameShape(QFrame::StyledPanel);
    mainLay->addWidget(groupBoxHV);
    QVBoxLayout* groupBoxKonfiguracjaHV = new QVBoxLayout(groupBoxHV);

    QHBoxLayout* groupBoxKonfiguracjaHV2 = new QHBoxLayout();
    groupBoxKonfiguracjaHV->addLayout(groupBoxKonfiguracjaHV2);
    ograniczenie = new QCheckBox("Ograniczenie:");
    groupBoxKonfiguracjaHV2->addWidget(ograniczenie);
    connect(ograniczenie, &QCheckBox::toggled, [this](bool checked){leMaxHV->setEnabled(checked);});
    connect(ograniczenie, &QCheckBox::released, [this](){this->ograniczHV("");});
    leMaxHV = new QLineEdit("01FF");
    leMaxHV->setMaximumWidth(50);
    leMaxHV->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leMaxHV->setValidator(new HexValidator(2, 1, leMaxHV));
    leMaxHV->setToolTip("Maksymalne napięcie pracy, magiczna, niewyskalowana liczba.");
    connect(leMaxHV, SIGNAL(textChanged(QString)), this, SLOT(ograniczHV(QString)));
    groupBoxKonfiguracjaHV2->addWidget(leMaxHV);
    ograniczenie->setChecked(true);

    QHBoxLayout* groupBoxKonfiguracjaHV1 = new QHBoxLayout();
    groupBoxKonfiguracjaHV->addLayout(groupBoxKonfiguracjaHV1);
    QLabel* hvl = new QLabel("Napięcie:");
    groupBoxKonfiguracjaHV1->addWidget(hvl);
    leHV = new QLineEdit("01FF");
    leHV->setMaximumWidth(50);
    leHV->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leHV->setValidator(new HexValidator(2, 1, leHV));
    leHV->setToolTip("Napięcie pracy, magiczna, niewyskalowana liczba.");
    connect(leHV, SIGNAL(textChanged(QString)), this, SLOT(ograniczHV(QString)));
    groupBoxKonfiguracjaHV1->addWidget(leHV);
    QHBoxLayout* groupbtns = new QHBoxLayout();
    groupBoxKonfiguracjaHV->addLayout(groupbtns);
    QPushButton* btns = new QPushButton("RESET_SLAVE");
    btns->setEnabled(false);
    btns->setToolTip("Według specyfikacji coś tam, kiedyś miało robić, teraz tylko zawiesza urządzenia.");
    connect(btns, &QPushButton::clicked, [this](){QByteArray a;a.append(char(0x03));a.append(char(myAdr));emit Send(a);});
    groupbtns->addWidget(btns);
    QPushButton* btnHV = new QPushButton("SET_HIGH_VOLTAGE");
    connect(btnHV, SIGNAL(clicked(bool)), this, SLOT(makeSET_HIGH_VOLTAGE()));
    connect(leHV, SIGNAL(returnPressed()), btnHV, SLOT(click()));
    groupbtns->addWidget(btnHV);

    QFrame* groupBoxGOT = new QFrame();
    groupBoxGOT->setFrameShape(QFrame::StyledPanel);
    mainLay->addWidget(groupBoxGOT);
    QVBoxLayout* groupBoxKonfiguracjaGOT = new QVBoxLayout(groupBoxGOT);
    QHBoxLayout* groupBoxKonfiguracjaGOT1 = new QHBoxLayout();
    groupBoxKonfiguracjaGOT->addLayout(groupBoxKonfiguracjaGOT1);
    QLabel* gotl = new QLabel("Wzmocnienie:");
    groupBoxKonfiguracjaGOT1->addWidget(gotl);
    kcbox = new QComboBox();
    kcbox->addItems(gnam);
    groupBoxKonfiguracjaGOT1->addWidget(kcbox);
    rozniczkowanie = new QCheckBox("Różniczkowanie");
    groupBoxKonfiguracjaGOT->addWidget(rozniczkowanie);
    QHBoxLayout* groupBoxKonfiguracjaGOT2 = new QHBoxLayout();
    groupBoxKonfiguracjaGOT->addLayout(groupBoxKonfiguracjaGOT2);
    gotl = new QLabel("Offset:");
    groupBoxKonfiguracjaGOT2->addWidget(gotl);
    leOFFSET = new QLineEdit("0000");
    leOFFSET->setMaximumWidth(50);
    leOFFSET->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leOFFSET->setValidator(new HexValidator(2, 1, leOFFSET));
    groupBoxKonfiguracjaGOT2->addWidget(leOFFSET);
    gotl = new QLabel("Trigger:");
    groupBoxKonfiguracjaGOT2->addWidget(gotl);
    leTRIGGER = new QLineEdit("0000");
    leTRIGGER->setMaximumWidth(50);
    leTRIGGER->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leTRIGGER->setValidator(new HexValidator(2, 1, leTRIGGER));
    groupBoxKonfiguracjaGOT2->addWidget(leTRIGGER);
    QPushButton* btnGOT = new QPushButton("SET_GAIN_OFFSET_AND_TRIGGER");
    connect(btnGOT, SIGNAL(clicked(bool)), this, SLOT(makeSET_GAIN_OFFSET_AND_TRIGGER()));
    connect(leTRIGGER, SIGNAL(returnPressed()), btnGOT, SLOT(click()));
    connect(leOFFSET, SIGNAL(returnPressed()), btnGOT, SLOT(click()));
    groupBoxKonfiguracjaGOT->addWidget(btnGOT);

    QFrame* groupBoxKAN = new QFrame();
    groupBoxKAN->setToolTip("Konfiguracja kanałów (max 12?). Każda wartość określa górną granicę wysokości\n"
                            "impulsu (według ADC, 12 bit?) który będzie zaliczony do tego kanału. Każdy \n"
                            "mierzony impuls jest dodawany ostatniego kanału w którego zakresie się zmieści.\n"
                            "Odcięcie od dołu jest ustawione przez trigger. Przykładowo, jeżeli podano kanały\n"
                            "0010 0020 to w pierwszym kanale znajdą się impulsy z zakresu trigger-0010, w \n"
                            "drugim z zakresu 0011-0020. Zaznaczenie opcji \"Ignoruj pierwszy kanał\" \n"
                            "spowoduje programowe odrzucenie pierwszego kanału.");
    groupBoxKAN->setFrameShape(QFrame::StyledPanel);
    mainLay->addWidget(groupBoxKAN);
    QVBoxLayout* groupBoxKonfiguracjaKAN = new QVBoxLayout(groupBoxKAN);
    QHBoxLayout* groupBoxKonfiguracjaKAN1 = new QHBoxLayout();
    groupBoxKonfiguracjaKAN->addLayout(groupBoxKonfiguracjaKAN1);
    QLabel* kanl = new QLabel("Kanały:");
    groupBoxKonfiguracjaKAN1->addWidget(kanl);
    leKANALY = new QLineEdit("0666 AAAA");
    leKANALY->setValidator(new HexValidator(2, 12, leKANALY));
    groupBoxKonfiguracjaKAN->addWidget(leKANALY);
    QPushButton* btnKAN = new QPushButton("SET_CHANNELS");
    connect(btnKAN, SIGNAL(clicked(bool)), this, SLOT(makeSET_CHANNELS()));
    groupBoxKonfiguracjaKAN1->addWidget(btnKAN);
    connect(leKANALY, SIGNAL(returnPressed()), btnKAN, SLOT(click()));

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));


//    const uint MIN_PB_W = 150;

//    QHBoxLayout* toAdrLay = new QHBoxLayout();
//    mainLay->addLayout(toAdrLay);
//    QLabel* lab = new QLabel("Adres docelowy:");
//    toAdrLay->addWidget(lab);
//    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    leToAdr = new QLineEdit("FF");
//    leToAdr->setInputMask("HH");
//    leToAdr->setMaximumWidth(40);
//    toAdrLay->addWidget(leToAdr);

//    QHBoxLayout* wkpSTORELay = new QHBoxLayout();
//    mainLay->addLayout(wkpSTORELay);
//    QPushButton* pb = new QPushButton("wkpSTORE");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpSTORE());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpSTORELay->addWidget(pb);
//    wkpSTORELay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpCONNECTLay = new QHBoxLayout();
//    mainLay->addLayout(wkpCONNECTLay);
//    pb = new QPushButton("wkpCONNECT");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECT());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpCONNECTLay->addWidget(pb);
//    wkpCONNECTLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpCONNECToLay = new QHBoxLayout();
//    mainLay->addLayout(wkpCONNECToLay);
//    pb = new QPushButton("wkpCONNECTo");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpCONNECTo(SU::string2ByteArray(leConnO->text())));});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpCONNECToLay->addWidget(pb);
//    wkpCONNECToLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    lab = new QLabel("Następnik:");
//    wkpCONNECToLay->addWidget(lab);
//    leConnO = new QLineEdit("FF");
//    leConnO->setInputMask("HH");
//    leConnO->setMaximumWidth(40);
//    wkpCONNECToLay->addWidget(leConnO);

//    QHBoxLayout* wkpBUILDLay = new QHBoxLayout();
//    mainLay->addLayout(wkpBUILDLay);
//    pb = new QPushButton("wkpBUILD");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILD());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpBUILDLay->addWidget(pb);
//    wkpBUILDLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpBUILDoLay = new QHBoxLayout();
//    mainLay->addLayout(wkpBUILDoLay);
//    pb = new QPushButton("wkpBUILDo");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpBUILDo());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpBUILDoLay->addWidget(pb);
//    wkpBUILDoLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

//    QHBoxLayout* wkpRESETLay = new QHBoxLayout();
//    mainLay->addLayout(wkpRESETLay);
//    pb = new QPushButton("wkpRESET");
//    connect(pb, &QPushButton::clicked, [this](){SendMessage(PureMessage::wkpRESET());});
//    pb->setMaximumWidth(MIN_PB_W);
//    pb->setMinimumWidth(MIN_PB_W);
//    wkpRESETLay->addWidget(pb);
//    wkpRESETLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
}

void KontrolerPomiarowy::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitRest();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();

    ograniczHV("");
}

void KontrolerPomiarowy::ograniczHV(QString)
{
    if(!ograniczenie->isChecked())
        return;

    int max = leMaxHV->text().toInt(nullptr, 16);
    int current = leHV->text().toInt(nullptr, 16);
    if(current>max)
        leHV->setText(leMaxHV->text());
}

void KontrolerPomiarowy::makeSET_HIGH_VOLTAGE()
{
    ograniczHV("");
    int hvval = leHV->text().toInt(nullptr, 16);
    QByteArray temp;
    temp.append(0x05);
    temp.append(myAdr);
    temp.append(hvval&0xFF);
    temp.append((hvval>>8)&0xFF);
    emit Send(temp);
}

void KontrolerPomiarowy::makeSET_GAIN_OFFSET_AND_TRIGGER()
{
    int offval = leOFFSET->text().toInt(nullptr, 16);
    int trival = leTRIGGER->text().toInt(nullptr, 16);
    QByteArray temp;
    temp.append(0x06);
    temp.append(myAdr);
    uchar gain = gval.value(kcbox->currentText(), 0);
    if(rozniczkowanie->isChecked())
        gain |= 0x08;
    temp.append(gain);
    temp.append(offval&0xFF);
    temp.append((offval>>8)&0xFF);
    temp.append(trival&0xFF);
    temp.append((trival>>8)&0xFF);
    emit Send(temp);
}

void KontrolerPomiarowy::makeSET_CHANNELS()
{
    QList<int> values;
    QString inString = leKANALY->text();
    if(inString.at(0)==' ')
        inString.remove(0, 1);
    if(inString.at(inString.size()-1)==' ')
        inString.remove(inString.size()-1, 1);
    QStringList vals = inString.split(' ');
    values.clear();
    for(QString str: vals)
        values.append(str.toInt(nullptr, 16));
    if(values.isEmpty())
    {
        emit Error("Brak zakresów");
        return;
    }

    QByteArray temp;
    temp.append(0x01);
    temp.append(myAdr);
    temp.append(values.size());

    for(int i: values)
    {
        temp.append(i&0xFF);
        temp.append((i>>8)&0xFF);
    }
    emit Send(temp);
}
