#include "LogicUIStawrov.hpp"
#include "../Factory.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include "utils_Stawrov/KontrolerPomiarowy.hpp"
#include <QLabel>
#include <QDebug>
#include <QMap>

LogicUIStawrov::LogicUIStawrov(QFrame* parent):
    LogicUI(parent),
    Restorable("LogicUIStawrov")
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

    synchTimer = new QTimer();
    connect(synchTimer, &QTimer::timeout, [this](){QByteArray a;a.append(char(0x02));a.append(char(0xFF));PackAndSend(a);});
    //fdsfa
}

LogicUIStawrov::~LogicUIStawrov()
{
    meanTimer->stop();

    Store("Adr", leAdr->text());
    Store("Data", leData->text());
    Store("FileLog", fileAdr->text());
    Store("lekAdr", lekAdr->text());
    Store("sbseconds", sbseconds->value());
    Store("cbIgnoreFirst", cbIgnoreFirst->isChecked());
    Store("leNewAdr", leNewAdr->text());
    Store("cbAutoSynch", cbAutoSynch->isChecked());
    Store("sbSynch", sbSynch->value());

    QStringList tabs;
    for(int i=0;i<tw->count();++i)
        tabs.append(tw->tabText(i));
    Store("tabs", tabs);

    delete logg;
    delete meanTimer;
    delete synchTimer;
}

void LogicUIStawrov::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitTests();

    LoadConfigs();

    logg->setIgnoringFirstChannel(cbIgnoreFirst->isChecked());
    TimeoutUpdate();
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
    mainWyslijCosLay->addWidget(btn);
//    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

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

    cbIgnoreFirst = new QCheckBox("Ignoruj pierwszy kanał");
    cbIgnoreFirst->setToolTip("Zaznaczenie tej opcji spowoduje programowe odrzucenie pierwszego kanału, \n"
                              "nie wpływa na działanie kontrolerów. Ogranicza efektywną liczę kanałów\n"
                              "o jeden.");
    mainZbieranieLay->addWidget(cbIgnoreFirst);
    connect(cbIgnoreFirst, &QCheckBox::toggled, [this](){logg->setIgnoringFirstChannel(cbIgnoreFirst->isChecked());});

    //=======================Grupa konfiguracja===================================================
    QGroupBox* groupBoxAll = new QGroupBox("Globalnie");
    mainLay->addWidget(groupBoxAll);
    QVBoxLayout* mainAllLay = new QVBoxLayout(groupBoxAll);

    QHBoxLayout* groupBoxKonfiguracja22 = new QHBoxLayout();
    QString ttxx = "Według specyfikacji protokołu adres kontrolera zliczającego. Według logiki zbędny, \n"
                   "nic nie wnoszący, mylący, dowolny adres. No ale specyfikacja to rzecz święta, więc jest.";
    QString ttyy = "Według specyfikacji coś tam, kiedyś miało robić, teraz tylko zawiesza urządzenia.";
    mainAllLay->addLayout(groupBoxKonfiguracja22);
    QPushButton* btns = new QPushButton("SYNCH_AND_START");
    btns->setToolTip(ttyy);
//    btns->setEnabled(false);
    connect(btns, &QPushButton::clicked, [this](){QByteArray a;a.append(char(0x02));a.append(char(0xFF));PackAndSend(a);});
    groupBoxKonfiguracja22->addWidget(btns);
    btns = new QPushButton("RESET_MASTER");
    btns->setEnabled(false);
    btns->setToolTip(ttyy);
    connect(btns, &QPushButton::clicked, [this](){QByteArray a;a.append(char(0x04));PackAndSend(a);});
    groupBoxKonfiguracja22->addWidget(btns);
    QLabel* tl23 = new QLabel("Adres master:");
    tl23->setToolTip(ttxx);
    groupBoxKonfiguracja22->addWidget(tl23);
    lekAdr = new QLineEdit("FF");
    lekAdr->setToolTip(ttxx);
    lekAdr->setMaximumWidth(50);
    lekAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lekAdr->setValidator(new HexValidator(1, 1, lekAdr));
    groupBoxKonfiguracja22->addWidget(lekAdr);

    QHBoxLayout* groupBoxKonfiguracja33 = new QHBoxLayout();
    mainAllLay->addLayout(groupBoxKonfiguracja33);
    cbAutoSynch = new QCheckBox("Automatyczna synchronizacja co ");
    connect(cbAutoSynch, SIGNAL(toggled(bool)), this, SLOT(TimeoutUpdate()));
    groupBoxKonfiguracja33->addWidget(cbAutoSynch);
    sbSynch = new QSpinBox();
    sbSynch->setMinimum(1);
    sbSynch->setMaximum(30);
    connect(sbSynch, SIGNAL(valueChanged(int)), this, SLOT(TimeoutUpdate()));
    groupBoxKonfiguracja33->addWidget(sbSynch);
    QLabel* tl23xx = new QLabel("minut.");
    groupBoxKonfiguracja33->addWidget(tl23xx);
    groupBoxKonfiguracja33->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

//    QFrame* groupBoxKAN = new QFrame();
//    groupBoxKAN->setToolTip("Konfiguracja kanałów (max 12?). Każda wartość określa górną granicę wysokości\n"
//                            "impulsu (według ADC, 12 bit?) który będzie zaliczony do tego kanału. Każdy \n"
//                            "mierzony impuls jest dodawany ostatniego kanału w którego zakresie się zmieści.\n"
//                            "Odcięcie od dołu jest ustawione przez trigger. Przykładowo, jeżeli podano kanały\n"
//                            "0010 0020 to w pierwszym kanale znajdą się impulsy z zakresu trigger-0010, w \n"
//                            "drugim z zakresu 0011-0020. Zaznaczenie opcji \"Ignoruj pierwszy kanał\" \n"
//                            "spowoduje programowe odrzucenie pierwszego kanału.");
//    groupBoxKAN->setFrameShape(QFrame::StyledPanel);
//    mainAllLay->addWidget(groupBoxKAN);
//    QVBoxLayout* groupBoxKonfiguracjaKAN = new QVBoxLayout(groupBoxKAN);
//    QHBoxLayout* groupBoxKonfiguracjaKAN1 = new QHBoxLayout();
//    groupBoxKonfiguracjaKAN->addLayout(groupBoxKonfiguracjaKAN1);
//    QLabel* kanl = new QLabel("Kanały:");
//    groupBoxKonfiguracjaKAN1->addWidget(kanl);
//    leKANALY = new QLineEdit("0666 AAAA");
//    leKANALY->setValidator(new HexValidator(2, 12, leKANALY));
//    groupBoxKonfiguracjaKAN->addWidget(leKANALY);
//    QPushButton* btnKAN = new QPushButton("SET_CHANNELS");
//    connect(btnKAN, SIGNAL(clicked(bool)), this, SLOT(makeSET_CHANNELS()));
//    groupBoxKonfiguracjaKAN1->addWidget(btnKAN);
//    connect(leKANALY, SIGNAL(returnPressed()), btnKAN, SLOT(click()));

    //=======================Grupa kontrolery pomiarowe===========================================
    QGroupBox* groupBoxPomiarowe = new QGroupBox("Kontrolery pomiarowe");
    mainLay->addWidget(groupBoxPomiarowe);
    QVBoxLayout* mainPomiaroweLay = new QVBoxLayout(groupBoxPomiarowe);

    QHBoxLayout* mainPomiaroweLay5 = new QHBoxLayout();
    mainPomiaroweLay->addLayout(mainPomiaroweLay5);
    btnremove = new QPushButton("Usuń aktywny");
    btnremove->setEnabled(false);
    btnremove->setToolTip("Usuwa aktywną zakładkę z kontrolerem pomiarowym.");
    mainPomiaroweLay5->addWidget(btnremove);
    connect(btnremove, SIGNAL(clicked(bool)), this, SLOT(RemoveTab()));
    QPushButton* btnx = new QPushButton("Dodaj");
    btnx->setToolTip("Dodaje nową zakładkę z kontrolerem pomiarowym o adresie podanym w polu po prawej.");
    mainPomiaroweLay5->addWidget(btnx);
    connect(btnx, &QPushButton::clicked, [this](){AddTab(leNewAdr->text());});
    QLabel* tlXXX = new QLabel("Dadaj adres:");
    mainPomiaroweLay5->addWidget(tlXXX);
    leNewAdr = new QLineEdit("FF");
    leNewAdr->setToolTip("Adres kontrolera pomiarowego jaki zostanie przypisany do nowo \n"
                         "utworzonej zakładki.");
    leNewAdr->setMaximumWidth(50);
    leNewAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leNewAdr->setValidator(new HexValidator(1, 1, lekAdr));
    mainPomiaroweLay5->addWidget(leNewAdr);
    connect(leNewAdr, SIGNAL(returnPressed()), btnx, SLOT(click()));

    tw = new QTabWidget();
    tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainPomiaroweLay->addWidget(tw);

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUIStawrov::LoadConfigs()
{
    leAdr->setText(RestoreAsString("Adr", "FE"));
    fileAdr->setText(RestoreAsString("FileLog", "defaultFileName.txt"));
    leData->setText(RestoreAsString("Data", "ff aa 55"));
    lekAdr->setText(RestoreAsString("lekAdr", "FF"));
    sbseconds->setValue(RestoreAsInt("sbseconds", 12));
    cbIgnoreFirst->setChecked(RestoreAsBool("cbIgnoreFirst", false));
    leNewAdr->setText(RestoreAsString("leNewAdr", "FF"));
    cbAutoSynch->setChecked(RestoreAsBool("cbAutoSynch", false));
    sbSynch->setValue(RestoreAsInt("sbSynch", 10));

    QStringList tablist = RestoreAsQStringList("tabs", QStringList());
    for(auto aadr: tablist)
        AddTab(aadr);
}

void LogicUIStawrov::Connected()
{
    btn->setEnabled(true);
    cParent->setEnabled(true);
    StopMeaning();
    TimeoutUpdate();
}

void LogicUIStawrov::Disconnected()
{
    btn->setEnabled(false);
    cParent->setEnabled(false);
    StopMeaning();
    synchTimer->stop();
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

void LogicUIStawrov::makeSET_CHANNELS()
{
    QList<int> values;
    QString inString;// = leKANALY->text();
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
    temp.append(0xFF);
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

void LogicUIStawrov::RemoveTab()
{
    if(tw->currentIndex()<0)
        return;

    delete tw->currentWidget();

    if(tw->count()<=0)
        btnremove->setEnabled(false);
}

void LogicUIStawrov::AddTab(QString adr)
{
    bool ok;
    int tempi = adr.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + adr);
        return;
    }

    if(tempi>0xFF)
    {
        emit Error("Nieprawidłowy adres: " + QString(tempi));
        return;
    }

    QString numstr = QString("%1").arg((uint)tempi&0xFF, 2, 16, QChar('0')).toUpper();

    for(int i=0;i<tw->count();++i)
    {
        if(!tw->tabText(i).compare(numstr))
        {
            emit Error("Zakładka z adresem kontrolera pomiarowego "+numstr+" już istnieje.");
            return;
        }
    }

    QFrame* fr = new QFrame(cParent);
    KontrolerPomiarowy* kp = new KontrolerPomiarowy(tempi, fr);
    connect(kp, SIGNAL(Send(QByteArray)), this, SLOT(PackAndSend(QByteArray)));
    tw->addTab(fr, numstr);
    btnremove->setEnabled(true);
}

void LogicUIStawrov::TimeoutUpdate()
{
    if(cbAutoSynch->isChecked())
        synchTimer->start(sbSynch->value()*1000*60);
    else
        synchTimer->stop();
}
