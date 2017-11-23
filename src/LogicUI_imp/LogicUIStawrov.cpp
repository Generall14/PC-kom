#include "LogicUIStawrov.hpp"
#include "../Factory.hpp"
#include "../Frame_imp/FrameStawrov.hpp"
#include <QLabel>
#include <QDebug>

LogicUIStawrov::LogicUIStawrov(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIStawrov";
    logg = new STawrovLogger("pustyPlikKropkaTeIksTe.txt");
    connect(logg, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(logg, SIGNAL(StateChanged(QString)), this, SLOT(setStatus(QString)), Qt::QueuedConnection);
    connect(logg, SIGNAL(SetChannels(int)), this, SLOT(setChannels(int)), Qt::QueuedConnection);
    logg->Reset("pustyPlikKropkaTeIksTe.txt");
}

LogicUIStawrov::~LogicUIStawrov()
{
    Store("configs/LogicUIStawrovAdr.cfg", leAdr->text());
    Store("configs/LogicUIStawrovHeader.cfg", leHeader->text());
    Store("configs/LogicUIStawrovData.cfg", leData->text());
    Store("configs/LogicUIStawrovFileLog.cfg", fileAdr->text());
    Store("configs/LogicUIStawrovleZakA.cfg", leZakA->text());
    Store("configs/LogicUIStawrovleAakB.cfg", leAakB->text());
    Store("configs/LogicUIStawrovlekAdr.cfg", lekAdr->text());
    Store("configs/LogicUIStawrovwarUlamki.cfg", warUlamki->text());
    Store("configs/LogicUIStawrovmetUlamki.cfg", QString::number((int)metUlamki->isChecked()));
    Store("configs/LogicUIStawrovlekAdrLoc.cfg", lekAdrLoc->text());

    delete logg;
}

void LogicUIStawrov::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitTests();

    LoadConfigs();
    checkMode();
}

void LogicUIStawrov::InitTests()
{
    //=======================Grupa wyslijcos======================================================
    QGroupBox* groupBoxWyslijCos = new QGroupBox("Wyślij coś");
    mainLay->addWidget(groupBoxWyslijCos);
    QVBoxLayout* mainWyslijCosLay = new QVBoxLayout(groupBoxWyslijCos);

    QHBoxLayout* groupBoxWyslijCosX = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosX);
    QLabel* tl1 = new QLabel("Nagłówek:");
    groupBoxWyslijCosX->addWidget(tl1);
    leHeader = new QLineEdit("fd");
    leHeader->setMaximumWidth(50);
    leHeader->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leHeader->setValidator(new HexValidator(1, 1, leHeader));
    groupBoxWyslijCosX->addWidget(leHeader);

    QHBoxLayout* groupBoxWyslijCosY = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosY);
    QLabel* tl2 = new QLabel("Adres:");
    groupBoxWyslijCosY->addWidget(tl2);
    leAdr = new QLineEdit("fe");
    leAdr->setMaximumWidth(50);
    leAdr->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leAdr->setValidator(new HexValidator(1, 1, leAdr));
    groupBoxWyslijCosY->addWidget(leAdr);

    QHBoxLayout* groupBoxWyslijCosZ = new QHBoxLayout();
    mainWyslijCosLay->addLayout(groupBoxWyslijCosZ);
    QLabel* tl3 = new QLabel("Dane:");
    groupBoxWyslijCosZ->addWidget(tl3);
    leData = new QLineEdit("ff aa 55");
    leData->setValidator(new HexValidator(1, 27, leData));
    groupBoxWyslijCosZ->addWidget(leData);

    btn = new QPushButton("Wyślij coś");
    mainWyslijCosLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    //=======================Grupa zbieranie danych===============================================
    QGroupBox* groupBoxZbieranie = new QGroupBox("Zbieranie danych");
    mainLay->addWidget(groupBoxZbieranie);
    QVBoxLayout* mainZbieranieLay = new QVBoxLayout(groupBoxZbieranie);

    QHBoxLayout* mainZbieranieLay1 = new QHBoxLayout();
    mainZbieranieLay->addLayout(mainZbieranieLay1);
    QLabel* tlab = new QLabel("Status:");
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
    fileAdr->setToolTip("Nazwa pliku, pisane do niego będzie dopiero po kliknięciu 'Reset'.");
    mainZbieranieLay2->addWidget(fileAdr);

    QPushButton* btnr = new QPushButton("Reset");
    mainZbieranieLay->addWidget(btnr);
    btnr->setToolTip("Resetuje zbieranie danych, rozpoczyna nowy pomiar w pliku o nazwie podanej wyżej (UWAGA! nadpisuje istniejące pliki).");
    connect(btnr, &QPushButton::clicked, [=](){logg->Reset(fileAdr->text());});

    //=======================Grupa konfiguracja===================================================
    QGroupBox* groupBoxKonfiguracja = new QGroupBox("Konfiguracja kontrolerów");
    mainLay->addWidget(groupBoxKonfiguracja);
    QVBoxLayout* mainKonfiguracjaLay = new QVBoxLayout(groupBoxKonfiguracja);

    QHBoxLayout* groupBoxKonfiguracja1 = new QHBoxLayout();
    mainKonfiguracjaLay->addLayout(groupBoxKonfiguracja1);
    tl1 = new QLabel("Zakres pracy (min - max):");
    groupBoxKonfiguracja1->addWidget(tl1);
    leZakA = new QLineEdit("fd");
    leZakA->setToolTip("Początek wykorzystywanego przedziału pomiarowego.");
    leZakA->setMaximumWidth(50);
    leZakA->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leZakA->setValidator(new HexValidator(2, 1, leZakA));
    groupBoxKonfiguracja1->addWidget(leZakA);
    leAakB = new QLineEdit("fd");
    leAakB->setToolTip("Koniec wykorzystywanego przedziału pomiarowego.");
    leAakB->setMaximumWidth(50);
    leAakB->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    leAakB->setValidator(new HexValidator(2, 1, leAakB));
    groupBoxKonfiguracja1->addWidget(leAakB);

    lll = new QLabel("Szerokości kanałów:");
    mainKonfiguracjaLay->addWidget(lll);
    QHBoxLayout* groupBoxKonfiguracja2 = new QHBoxLayout();
    mainKonfiguracjaLay->addLayout(groupBoxKonfiguracja2);

    QVBoxLayout* checkLay = new QVBoxLayout();
    groupBoxKonfiguracja2->addLayout(checkLay);
    metUlamki = new QRadioButton("Tak:");
    checkLay->addWidget(metUlamki);
    metUlamki->setChecked(true);
    metUlamki->setToolTip("Tu się podaje szerokości kanałów jako ułamki całego przedziału podanego wyżej.");
    connect(metUlamki, SIGNAL(toggled(bool)), this, SLOT(checkMode()));
    metWartosci = new QRadioButton("Inaczej:");
    metWartosci->setToolTip("Te wartości będą bezpośrednio przesłane do kontrolera.");
    connect(metWartosci, SIGNAL(toggled(bool)), this, SLOT(checkMode()));
    checkLay->addWidget(metWartosci);

    QVBoxLayout* checkLay2 = new QVBoxLayout();
    groupBoxKonfiguracja2->addLayout(checkLay2);
    warUlamki = new QLineEdit("0.5 0.5");
    warUlamki->setValidator(new ValidateDumbFloat(warUlamki));
    warUlamki->setToolTip("Tu się podaje szerokości kanałów jako ułamki całego przedziału podanego wyżej.");
    connect(warUlamki, SIGNAL(editingFinished()), this, SLOT(CalcChannels()), Qt::QueuedConnection);
    checkLay2->addWidget(warUlamki);
    warWartosci = new QLineEdit("0666 AAAA");
    warWartosci->setValidator(new HexValidator(2, 12, warWartosci));
    warWartosci->setToolTip("Te wartości będą bezpośrednio przesłane do kontrolera.");
    connect(warWartosci, SIGNAL(editingFinished()), this, SLOT(CalcChannels()), Qt::QueuedConnection);
    checkLay2->addWidget(warWartosci);

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

    btnr2 = new QPushButton("Przelicz i wyślij");
    btnr2->setToolTip("Przelicz kanały i wyślij komunikat na wskazany adres.");
    mainKonfiguracjaLay->addWidget(btnr2);
    connect(btnr2, SIGNAL(clicked(bool)), this, SLOT(SendConfig()));

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));
}

void LogicUIStawrov::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUIStawrovAdr.cfg", temp))
        leAdr->setText(temp);
    if(!Restore("configs/LogicUIStawrovHeader.cfg", temp))
        leHeader->setText(temp);
    if(!Restore("configs/LogicUIStawrovData.cfg", temp))
        leData->setText(temp);
    if(!Restore("configs/LogicUIStawrovFileLog.cfg", temp))
        fileAdr->setText(temp);
    if(!Restore("configs/LogicUIStawrovleZakA.cfg", temp))
        leZakA->setText(temp);
    if(!Restore("configs/LogicUIStawrovleAakB.cfg", temp))
        leAakB->setText(temp);
    if(!Restore("configs/LogicUIStawrovlekAdr.cfg", temp))
        lekAdr->setText(temp);
    if(!Restore("configs/LogicUIStawrovwarUlamki.cfg", temp))
        warUlamki->setText(temp);
    if(!Restore("configs/LogicUIStawrovlekAdrLoc.cfg", temp))
        lekAdrLoc->setText(temp);
    if(!Restore("configs/LogicUIStawrovmetUlamki.cfg", temp))
    {
        bool first = temp.toInt();
        if(!first)
            metWartosci->setChecked(true);
    }

    CalcChannels();
}

void LogicUIStawrov::Connected()
{
    btn->setEnabled(true);
    btnr2->setEnabled(true);
}

void LogicUIStawrov::Disconnected()
{
    btn->setEnabled(false);
    btnr2->setEnabled(false);
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
    QByteArray maker;
    maker.append(0xFF);

    QString stemp = leHeader->text().left(2);
    int tint = 0;
    bool ok;
    tint = stemp.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane nagłówka \""+stemp+"\".");
        return;
    }
    maker.append(tint&0xFF);

    stemp = leAdr->text().left(2);
    tint = stemp.toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Kijowe dane adresu \""+stemp+"\".");
        return;
    }
    maker.append(tint&0xFF);

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

    maker.append(dataArray.size()&0xFF);
    maker.append(dataArray);
    maker = FrameStawrov::AddCRC16(maker);

    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(maker)));
}

void LogicUIStawrov::setStatus(QString s)
{
    statusLabel->setText(s);
}

void LogicUIStawrov::setChannels(int s)
{
    channelsLabel->setText(QString::number(s));
}

/**
 * Sprawdza wybrany tryb wprowadzania kanałów i odpowiednio enabluje edytory.
 */
void LogicUIStawrov::checkMode()
{
    if(metUlamki->isChecked())
    {
        modeFromSizes = true;
        warUlamki->setEnabled(true);
        warWartosci->setEnabled(false);
    }
    else
    {
        modeFromSizes = false;
        warUlamki->setEnabled(false);
        warWartosci->setEnabled(true);
    }
}

/**
 * Przelicza przedziały podane w ułamkach na wartości i odwrotnie, w zależności od wybranej opcji. Wyniki przekazuje do values.
 * @return false - ok
 */
bool LogicUIStawrov::CalcChannels()
{
    int valMin = leZakA->text().toInt(NULL, 16);
    int valMax = leAakB->text().toInt(NULL, 16);
    if(!((valMin>=0)&&(valMax>0)&&(valMin<0xFFFF)&&(valMax<=0xFFFF)&&(valMax>valMin)))
    {
        emit Error("Błędne zakresy");
        return 1;
    }

    if(!modeFromSizes)
    {
        QString inString = warWartosci->text();
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
            return 1;
        }
        if((values.at(0)<valMin)||(values.last()>valMax))
        {
            emit Error("Progi poza zakresami");
            return 1;
        }
        for(int i=1;i<values.size();i++)
        {
            if(values.at(i)<values.at(i-1))
            {
                emit Error("Malejący ciąg progów");
                return 1;
            }
        }

        QList<float> fvals;
        values.insert(0, valMin);
        for(int i=1;i<values.size();i++)
            fvals.append((float)(values.at(i)-values.at(i-1))/(float)(valMax-valMin));
        values.removeAt(0);

        QString vtemp;
        for(float f: fvals)
            vtemp.append(" " + QString::number(f, 'g', 2));
        vtemp.remove(0, 1);
        warUlamki->setText(vtemp);
    }
    else
    {
        QString inString = warUlamki->text();
        if(inString.at(0)==' ')
            inString.remove(0, 1);
        if(inString.at(inString.size()-1)==' ')
            inString.remove(inString.size()-1, 1);
        QStringList vals = inString.split(' ');
        QList<float> fvals;
        bool ok;
        for(QString str: vals)
        {
            fvals.append(str.toFloat(&ok));
            if(!ok)
            {
                emit Error("Nie można odczytać wartości: " + str);
                return 1;
            }
        }
        float sum = 0;
        for(auto f: fvals)
        {
            if(f<=0)
            {
                emit Error("Nieprawidłowa wartość: " + QString::number(f));
                return 1;
            }
            sum += f;
        }
        if(sum>1.1)
        {
            emit Error("Suma ułamków grubo przekroczyła jedność: " + QString::number(sum));
            return 1;
        }

        values.clear();
        float csum = 0;
        QString temps;
        for(auto f: fvals)
        {
            csum += f;
            values.append(valMin+(((float)(valMax-valMin))*csum));
            temps.append(QString("%1 ").arg(values.last(), 4, 16, QChar('0')));
        }
        warWartosci->setText(temps);
    }
    values.insert(0, valMin);
    return 0;
}

/**
 * Buduje i wysyła komendę z konfiguracją.
 */
void LogicUIStawrov::SendConfig()
{
    if(CalcChannels())
        return;
    if(values.size()<2)
        return;
    QByteArray temp;
    temp.append(0xff);
    temp.append(0xfd);
    bool ok;
    int tempi = lekAdr->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu: " + lekAdr->text());
        return;
    }
    temp.append(tempi);

    QByteArray cargo;
    cargo.append(0x01);
    tempi = lekAdrLoc->text().toInt(&ok, 16);
    if(!ok)
    {
        emit Error("Nie można odczytać adresu lokalnego: " + lekAdrLoc->text());
        return;
    }
    cargo.append(tempi);
    cargo.append((values.size()-1)&0xFF);
    for(int i: values)
    {
        cargo.append(i&0xFF);
        cargo.append((i>>8)&0xFF);
    }

    temp.append(cargo.size()&0xFF);
    temp.append(cargo);
    temp = FrameStawrov::AddCRC16(temp);
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(temp)));
}
