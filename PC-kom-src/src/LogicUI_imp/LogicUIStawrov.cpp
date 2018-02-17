#include "LogicUIStawrov.hpp"
#include "../Factory.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include <QLabel>
#include <QDebug>
#include <QMap>

LogicUIStawrov::LogicUIStawrov(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIStawrov";
    logg = new STawrovLogger();
    connect(logg, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(logg, SIGNAL(StateChanged(QString)), this, SLOT(setStatus(QString)), Qt::QueuedConnection);
    connect(logg, SIGNAL(SetChannels(int)), this, SLOT(setChannels(int)), Qt::QueuedConnection);
    connect(logg, SIGNAL(File(QString)), this, SLOT(setFile(QString)), Qt::QueuedConnection);

    gnam.append("[010] x0.3"); gval.insertMulti(gnam.at(0), 0x02);
    gnam.append("[110] x0.6"); gval.insertMulti(gnam.at(1), 0x06);
    gnam.append("[000] x1.15"); gval.insertMulti(gnam.at(2), 0x00);
    gnam.append("[011] x2"); gval.insertMulti(gnam.at(3), 0x03);
    gnam.append("[111] x4"); gval.insertMulti(gnam.at(4), 0x07);
    gnam.append("[001] x7.5"); gval.insertMulti(gnam.at(5), 0x01);
    gnam.append("[101] x15"); gval.insertMulti(gnam.at(6), 0x05);

    meanTimer = new QTimer();
    meanTimer->setSingleShot(true);
    connect(meanTimer, SIGNAL(timeout()), this, SLOT(TimeoutedMean()));
}

LogicUIStawrov::~LogicUIStawrov()
{
    meanTimer->stop();

    Store("configs/LogicUIStawrovAdr.cfg", leAdr->text());
    Store("configs/LogicUIStawrovData.cfg", leData->text());
    Store("configs/LogicUIStawrovFileLog.cfg", fileAdr->text());
    Store("configs/LogicUIStawrovlekAdr.cfg", lekAdr->text());
    Store("configs/LogicUIStawrovlekAdrLoc.cfg", lekAdrLoc->text());
    Store("configs/LogicUIStawrovleHV.cfg", leHV->text());
    Store("configs/LogicUIStawrovleMaxHV.cfg", leMaxHV->text());
    Store("configs/LogicUIStawrovlekcbox.cfg", kcbox->currentText());
    Store("configs/LogicUIStawrovmetrozniczkowanie.cfg", QString::number((int)rozniczkowanie->isChecked()));
    Store("configs/LogicUIStawrovleOFFSET.cfg", leOFFSET->text());
    Store("configs/LogicUIStawrovleTRIGGER.cfg", leTRIGGER->text());
    Store("configs/LogicUIStawrovleKANALY.cfg", leKANALY->text());
    Store("configs/LogicUIStawrovsbseconds.cfg", QString::number(sbseconds->value()));

    delete logg;
    delete meanTimer;
}

void LogicUIStawrov::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitTests();

    LoadConfigs();

    ograniczHV("");
}

void LogicUIStawrov::InitTests()
{
    //=======================Grupa wyslijcos======================================================
    QGroupBox* groupBoxWyslijCos = new QGroupBox("Wyślij coś");
//    mainLay->addWidget(groupBoxWyslijCos);
    QVBoxLayout* mainWyslijCosLay = new QVBoxLayout(groupBoxWyslijCos);

    QHBoxLayout* groupBoxWyslijCosY = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosY);
    QLabel* tl2 = new QLabel("Adres:");
    groupBoxWyslijCosY->addWidget(tl2);
    leAdr = new QLineEdit("fe");
    leAdr->setMaximumWidth(50);
    leAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leAdr->setValidator(new HexValidator(1, 1, leAdr));
//    groupBoxWyslijCosY->addWidget(leAdr);

    QHBoxLayout* groupBoxWyslijCosZ = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosZ);
    QLabel* tl3 = new QLabel("Dane:");
    groupBoxWyslijCosZ->addWidget(tl3);
    leData = new QLineEdit("ff aa 55");
    leData->setValidator(new HexValidator(1, 27, leData));
//    groupBoxWyslijCosZ->addWidget(leData);

    btn = new QPushButton("Wyślij coś");
//    mainWyslijCosLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    //=======================Grupa zbieranie danych===============================================
    QGroupBox* groupBoxZbieranie = new QGroupBox("Zbieranie danych");
    mainLay->addWidget(groupBoxZbieranie);
    QVBoxLayout* mainZbieranieLay = new QVBoxLayout(groupBoxZbieranie);

    QHBoxLayout* mainZbieranieLay4 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay4);
    QLabel* tlab = new QLabel("Plik:");
    mainZbieranieLay4->addWidget(tlab);
    fileLabel = new QLabel("---");
    fileLabel->setAlignment(Qt::AlignRight);
    mainZbieranieLay4->addWidget(fileLabel);

    QHBoxLayout* mainZbieranieLay1 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay1);
    tlab = new QLabel("Status:");
    mainZbieranieLay1->addWidget(tlab);
    statusLabel = new QLabel("---");
    statusLabel->setAlignment(Qt::AlignRight);
    mainZbieranieLay1->addWidget(statusLabel);

    QHBoxLayout* mainZbieranieLay3 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay3);
    tlab = new QLabel("Kanały:");
    mainZbieranieLay3->addWidget(tlab);
    channelsLabel = new QLabel("-");
    channelsLabel->setAlignment(Qt::AlignRight);
    mainZbieranieLay3->addWidget(channelsLabel);

    QHBoxLayout* mainZbieranieLay2 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay2);
    QLabel* lll = new QLabel("Nazwa pliku:");
    mainZbieranieLay2->addWidget(lll);
    fileAdr = new QLineEdit("defaultFileName.txt");
    fileAdr->setToolTip("Nazwa pliku, pisane do niego będzie dopiero po kliknięciu 'Nowy plik'.");
    mainZbieranieLay2->addWidget(fileAdr);

    QPushButton* btnr = new QPushButton("Nowy plik");
    mainZbieranieLay->addWidget(btnr);
    btnr->setToolTip("Resetuje zbieranie danych, rozpoczyna nowy pomiar w pliku o nazwie podanej wyżej (UWAGA! nadpisuje istniejące pliki).");
    connect(btnr, &QPushButton::clicked, [=](){logg->Reset(fileAdr->text());});

    QHBoxLayout* mainZbieranieLay5 = new QHBoxLayout();
    QString tooltip = "Dane będą zbierane i uśredniane od wciśnięcia 'Start' do wciścięcia 'Stop' \n"
                      "lub minięcia czasu podanego w SpinBoxie (w sekundach), podanie wartości '0' \n"
                      "wyłącza czasowe zatrzymywanie uśredniania. Wyniki co sekundę wysyłąne są na \n"
                      "std::cout oraz po zakończeniu uśredniania do pliku 'Pomiary/mean.txt' (w trybie \nappend).";
    mainZbieranieLay->addLayout(mainZbieranieLay5);
    QLabel* llly = new QLabel("Uśrednianie:");
    llly->setToolTip(tooltip);
    mainZbieranieLay5->addWidget(llly);
    btnms = new QPushButton("Start");
    btnms->setToolTip(tooltip);
    mainZbieranieLay5->addWidget(btnms);
    connect(btnms, SIGNAL(clicked(bool)), this, SLOT(StartMeaning()));
    btnme = new QPushButton("Stop");
    btnme->setToolTip(tooltip);
    mainZbieranieLay5->addWidget(btnme);
    connect(btnme, SIGNAL(clicked(bool)), this, SLOT(StopMeaning()));

    seconds = new QLabel("0/");
    seconds->setToolTip(tooltip);
    seconds->setMinimumWidth(25);
    seconds->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    mainZbieranieLay5->addWidget(seconds);
    sbseconds = new QSpinBox();
    sbseconds->setToolTip(tooltip);
    mainZbieranieLay5->addWidget(sbseconds);
    sbseconds->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sbseconds->setMinimum(0);
    sbseconds->setMaximum(9999);
    QLabel* lllx = new QLabel("[s]");
    mainZbieranieLay5->addWidget(lllx);
    lllx->setToolTip(tooltip);

    //=======================Grupa konfiguracja===================================================
    QGroupBox* groupBoxKonfiguracja = new QGroupBox("Konfiguracja kontrolerów");
    mainLay->addWidget(groupBoxKonfiguracja);
    QVBoxLayout* mainKonfiguracjaLay = new QVBoxLayout(groupBoxKonfiguracja);

    QHBoxLayout* groupBoxKonfiguracja22 = new QHBoxLayout();
    mainKonfiguracjaLay->addLayout(groupBoxKonfiguracja22);
    QLabel* tl23 = new QLabel("Wyślij na adres:");
    groupBoxKonfiguracja22->addWidget(tl23);
    lekAdr = new QLineEdit("FF");
    lekAdr->setMaximumWidth(50);
    lekAdr->setToolTip("Adres docelowy komendy z konfiguracją szerokości kanałów.");
    lekAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lekAdr->setValidator(new HexValidator(1, 1, lekAdr));
    groupBoxKonfiguracja22->addWidget(lekAdr);

    QHBoxLayout* groupBoxKonfiguracja23 = new QHBoxLayout();
    mainKonfiguracjaLay->addLayout(groupBoxKonfiguracja23);
    tl23 = new QLabel("Wyślij na adres lokalny:");
    groupBoxKonfiguracja23->addWidget(tl23);
    lekAdrLoc = new QLineEdit("FF");
    lekAdrLoc->setMaximumWidth(50);
    lekAdrLoc->setToolTip("Docelowy adres lokalny komendy z konfiguracją szerokości kanałów.");
    lekAdrLoc->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lekAdrLoc->setValidator(new HexValidator(1, 1, lekAdrLoc));

    groupBoxKonfiguracja23->addWidget(lekAdrLoc);

    QFrame* groupBoxS = new QFrame();
    groupBoxS->setFrameShape(QFrame::StyledPanel);
    mainKonfiguracjaLay->addWidget(groupBoxS);
    QHBoxLayout* groupBoxKonfiguracjaSimple = new QHBoxLayout(groupBoxS);

    QPushButton* btns = new QPushButton("SYNCH_AND_START");
    connect(btns, SIGNAL(clicked(bool)), this, SLOT(makeSYNCH_AND_START()));
    groupBoxKonfiguracjaSimple->addWidget(btns);
    btns = new QPushButton("RESET_SLAVE");
    connect(btns, SIGNAL(clicked(bool)), this, SLOT(makeRESET_SLAVE()));
    groupBoxKonfiguracjaSimple->addWidget(btns);
    btns = new QPushButton("RESET_MASTER");
    connect(btns, SIGNAL(clicked(bool)), this, SLOT(makeRESET_MASTER()));
    groupBoxKonfiguracjaSimple->addWidget(btns);

    QFrame* groupBoxHV = new QFrame();
    groupBoxHV->setFrameShape(QFrame::StyledPanel);
    mainKonfiguracjaLay->addWidget(groupBoxHV);
    QVBoxLayout* groupBoxKonfiguracjaHV = new QVBoxLayout(groupBoxHV);

    QHBoxLayout* groupBoxKonfiguracjaHV2 = new QHBoxLayout();
    groupBoxKonfiguracjaHV->addLayout(groupBoxKonfiguracjaHV2);
    ograniczenie = new QCheckBox("Ograniczenie:");
    groupBoxKonfiguracjaHV2->addWidget(ograniczenie);
    connect(ograniczenie, &QCheckBox::toggled, [=](bool checked){leMaxHV->setEnabled(checked);});
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
    QPushButton* btnHV = new QPushButton("SET_HIGH_VOLTAGE");
    connect(btnHV, SIGNAL(clicked(bool)), this, SLOT(makeSET_HIGH_VOLTAGE()));
    groupBoxKonfiguracjaHV->addWidget(btnHV);

    QFrame* groupBoxGOT = new QFrame();
    groupBoxGOT->setFrameShape(QFrame::StyledPanel);
    mainKonfiguracjaLay->addWidget(groupBoxGOT);
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
    groupBoxKonfiguracjaGOT->addWidget(btnGOT);

    QFrame* groupBoxKAN = new QFrame();
    groupBoxKAN->setFrameShape(QFrame::StyledPanel);
    mainKonfiguracjaLay->addWidget(groupBoxKAN);
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

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUIStawrov::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUIStawrovAdr.cfg", temp))
        leAdr->setText(temp);
    if(!Restore("configs/LogicUIStawrovData.cfg", temp))
        leData->setText(temp);
    if(!Restore("configs/LogicUIStawrovFileLog.cfg", temp))
    {
        fileAdr->setText(temp);
        logg->Reset(temp);
    }
    else
        logg->Reset("pustyPlikKropkaTeIksTe.txt");
    if(!Restore("configs/LogicUIStawrovlekAdr.cfg", temp))
        lekAdr->setText(temp);
    if(!Restore("configs/LogicUIStawrovlekAdrLoc.cfg", temp))
        lekAdrLoc->setText(temp);
    if(!Restore("configs/LogicUIStawrovleHV.cfg", temp))
        leHV->setText(temp);
    if(!Restore("configs/LogicUIStawrovleMaxHV.cfg", temp))
        leMaxHV->setText(temp);
    if(!Restore("configs/LogicUIStawrovlekcbox.cfg", temp))
        kcbox->setCurrentText(temp);
    if(!Restore("configs/LogicUIStawrovleOFFSET.cfg", temp))
        leOFFSET->setText(temp);
    if(!Restore("configs/LogicUIStawrovleTRIGGER.cfg", temp))
        leTRIGGER->setText(temp);
    if(!Restore("configs/LogicUIStawrovleKANALY.cfg", temp))
        leKANALY->setText(temp);
    if(!Restore("configs/LogicUIStawrovmetrozniczkowanie.cfg", temp))
    {
        bool first = temp.toInt();
        if(first)
            rozniczkowanie->setChecked(true);
    }
    if(!Restore("configs/LogicUIStawrovsbseconds.cfg", temp))
    {
        bool ok;
        int vv = temp.toInt(&ok);
        if(ok)
            sbseconds->setValue(vv);
    }
}

void LogicUIStawrov::Connected()
{
    btn->setEnabled(true);
    cParent->setEnabled(true);
    StopMeaning();
}

void LogicUIStawrov::Disconnected()
{
    btn->setEnabled(false);
    cParent->setEnabled(false);
    StopMeaning();
}

void LogicUIStawrov::FrameReaded(QSharedPointer<Frame> frame)
{
    logg->FrameReaded(frame);
    frame.isNull();
}

/**
 * Tworzy wiadomość z wpisanymi danymi.
 */
void LogicUIStawrov::makeStupidMessage()
{
    bool ok;
    QString stemp;
    int tint;
    QByteArray maker;
    maker.append(0xFF);
    maker.append(0xFD);

    QByteArray dataArray;
    for(QString tttemp: leData->text().split(" "))
    {
        stemp = tttemp.left(2);
        if(stemp.isEmpty())
            continue;
        tint = stemp.toInt(&ok, 16);
        if(!ok)
        {
            emit Error("Kijowe dane danych \""+stemp+"\".");
            return;
        }
        dataArray.append(tint&0xFF);
    }

    stemp = leAdr->text().left(2);
    tint = stemp.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+stemp+"\".");
        return;
    }
    maker.append(tint&0xFF);
    maker.append(dataArray.size()&0xFF);
    maker.append(dataArray);
    maker = FrameStawrov::AddCRC16(maker);

    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(maker)));
}

void LogicUIStawrov::setStatus(QString s)
{
    statusLabel->setText(s);
}

void LogicUIStawrov::setFile(QString s)
{
    fileLabel->setText(s);
}

void LogicUIStawrov::setChannels(int s)
{
    channelsLabel->setText(QString::number(s));
}

void LogicUIStawrov::ograniczHV(QString)
{
    if(!ograniczenie->isChecked())
        return;

    int max = leMaxHV->text().toInt(nullptr, 16);
    int current = leHV->text().toInt(nullptr, 16);
    if(current>max)
        leHV->setText(leMaxHV->text());
}

void LogicUIStawrov::makeSYNCH_AND_START()
{
    QByteArray temp;
    temp.append(0x02);
    PackAndSend(temp);
}

void LogicUIStawrov::makeRESET_SLAVE()
{
    QByteArray temp;
    temp.append(0x03);
    bool ok;
    int tempi = lekAdrLoc->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }
    temp.append(tempi);
    PackAndSend(temp);
}

void LogicUIStawrov::makeRESET_MASTER()
{
    QByteArray temp;
    temp.append(0x04);
    PackAndSend(temp);
}

void LogicUIStawrov::makeSET_HIGH_VOLTAGE()
{
    ograniczHV("");
    int hvval = leHV->text().toInt(NULL, 16);
    QByteArray temp;
    temp.append(0x05);
    bool ok;
    int tempi = lekAdrLoc->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }
    temp.append(tempi);
    temp.append(hvval&0xFF);
    temp.append((hvval>>8)&0xFF);
    PackAndSend(temp);
}

void LogicUIStawrov::makeSET_GAIN_OFFSET_AND_TRIGGER()
{
    int offval = leOFFSET->text().toInt(NULL, 16);
    int trival = leTRIGGER->text().toInt(NULL, 16);
    QByteArray temp;
    temp.append(0x06);
    bool ok;
    int tempi = lekAdrLoc->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }
    temp.append(tempi);
    uchar gain = gval.value(kcbox->currentText(), 0);
    if(rozniczkowanie->isChecked())
        gain |= 0x08;
    temp.append(gain);
    temp.append(offval&0xFF);
    temp.append((offval>>8)&0xFF);
    temp.append(trival&0xFF);
    temp.append((trival>>8)&0xFF);
    PackAndSend(temp);
}

void LogicUIStawrov::makeSET_CHANNELS()
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
        values.append(str.toInt(NULL, 16));
    if(values.isEmpty())
    {
        emit Error("Brak zakresów");
        return;
    }

    QByteArray temp;
    temp.append(0x01);
    bool ok;
    int tempi = lekAdrLoc->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }
    temp.append(tempi);
    temp.append(values.size());

    for(int i: values)
    {
        temp.append(i&0xFF);
        temp.append((i>>8)&0xFF);
    }
    PackAndSend(temp);
}

void LogicUIStawrov::PackAndSend(QByteArray data)
{
    bool ok;
    int tempi = lekAdr->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }

    QByteArray temp;
    temp.append(0xFF);
    temp.append(0xFD);
    temp.append(tempi);
    temp.append((uchar)data.length());
    temp.append(data);
    temp = FrameStawrov::AddCRC16(temp);
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(temp)));
}

void LogicUIStawrov::StartMeaning()
{
    btnme->setEnabled(true);
    btnms->setEnabled(false);
    logg->startMeaning();
    secondsOfMeaning = 0;
    meanTimer->start(1000);
    seconds->setText("0 /");
}

void LogicUIStawrov::StopMeaning()
{
    btnme->setEnabled(false);
    btnms->setEnabled(true);
    logg->stopMeaning();
    meanTimer->stop();
}

void LogicUIStawrov::TimeoutedMean()
{
    secondsOfMeaning++;
    seconds->setText(QString::number(secondsOfMeaning)+" /");
    meanTimer->start(1000);
    logg->displayMean();
    if(sbseconds->value()>0)
    {
        if(secondsOfMeaning>=sbseconds->value())
            this->StopMeaning();
    }
}
