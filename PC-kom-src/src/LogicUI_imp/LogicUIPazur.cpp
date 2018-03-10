#include "LogicUIPazur.hpp"
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include <QDebug>

LogicUIPazur::LogicUIPazur(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIPazur";
}

LogicUIPazur::~LogicUIPazur()
{
//    Store("configs/LogicUITerminalsbBytes.cfg", sbBytes->text());
//    Store("configs/LogicUITerminalleSHexSign.cfg", leSHexSign->text());
//    Store("configs/LogicUITerminalinputsMethods.cfg", kbSWprowadzanie->currentText());
//    Store("configs/LogicUITerminalkbRWyswietanie.cfg", kbRWyswietanie->currentText());
//    Store("configs/LogicUITerminalleRHexSign.cfg", leRHexSign->text());
//    Store("configs/LogicUITerminalleRInvalid.cfg", leRInvalid->text());

//    for(int i=0;i<sends.length();i++)
//        Store("configs/LogicUITerminalleSend"+QString::number(i)+".cfg", sends.at(i)->Store());

//    for(int i=0;i<sends.length();i++)
//        delete sends[i];
//    sends.clear();
}

void LogicUIPazur::LoadConfigs()
{
//    QString temp;

//    if(!Restore("configs/LogicUITerminalleSHexSign.cfg", temp))
//        leSHexSign->setText(temp);
//    if(!Restore("configs/LogicUITerminalinputsMethods.cfg", temp))
//        kbSWprowadzanie->setCurrentText(temp);
//    if(!Restore("configs/LogicUITerminalkbRWyswietanie.cfg", temp))
//        kbRWyswietanie->setCurrentText(temp);
//    if(!Restore("configs/LogicUITerminalleRHexSign.cfg", temp))
//        leRHexSign->setText(temp);
//    if(!Restore("configs/LogicUITerminalleRInvalid.cfg", temp))
//        leRInvalid->setText(temp);
//    bool ok;
//    int vale;
//    if(!Restore("configs/LogicUITerminalsbBytes.cfg", temp))
//    {
//        vale = temp.toInt(&ok);
//        if(ok)
//            sbBytes->setValue(vale);
//    }
//    for(int i=0;i<sends.length();i++)
//    {
//        if(!Restore("configs/LogicUITerminalleSend"+QString::number(i)+".cfg", temp))
//            sends.at(i)->Restore(temp);
//    }
}

void LogicUIPazur::Init()
{
//    mainLay = new QVBoxLayout(cParent);
//    mainLay->setMargin(2);

//    InitReceive();
//    InitDisplay();
//    InitSend();

//    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

//    LoadConfigs();

//    SendReceivingParams();
//    SendDisplayParams();
}

//void LogicUITerminal::InitReceive()
//{
//    QString tooltip = "Dane będą wyświetlone gdy zostanie uzbierana odpowiednia ilość bajtów lub upłynie timeout od odebrania pierwszego bajtu w pakiecie";

//    QGroupBox* groupBoxOdbieranie = new QGroupBox("Odbieranie");
//    groupBoxOdbieranie->setToolTip(tooltip);
//    mainLay->addWidget(groupBoxOdbieranie);
//    QVBoxLayout* mainOdbieranie = new QVBoxLayout(groupBoxOdbieranie);

//    QHBoxLayout* bytesLay = new QHBoxLayout();
//    mainOdbieranie->addLayout(bytesLay);
//    QLabel* lab = new QLabel("Bajtów w pakiecie:");
//    bytesLay->addWidget(lab);
//    bytesLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    sbBytes = new QSpinBox();
//    sbBytes->setMinimum(1);
//    sbBytes->setMaximum(50);
//    sbBytes->setValue(10);
//    connect(sbBytes, SIGNAL(valueChanged(int)), this, SLOT(SendReceivingParams()));
//    bytesLay->addWidget(sbBytes);

//    QHBoxLayout* timeoutLay = new QHBoxLayout();
//    mainOdbieranie->addLayout(timeoutLay);
//    lab = new QLabel("Timeout pakietu [ms]:");
//    timeoutLay->addWidget(lab);
//    timeoutLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    sbTimeout = new QSpinBox();
//    sbTimeout->setMinimum(10);
//    sbTimeout->setMaximum(5000);
//    sbTimeout->setValue(100);
//    connect(sbTimeout, SIGNAL(valueChanged(int)), this, SLOT(SendReceivingParams()));
//    timeoutLay->addWidget(sbTimeout);
//}

//void LogicUITerminal::InitDisplay()
//{
//    QGroupBox* groupBoxWyswietlanie = new QGroupBox("Wyświetlanie");
//    mainLay->addWidget(groupBoxWyswietlanie);
//    QVBoxLayout* mainWyswietlanie = new QVBoxLayout(groupBoxWyswietlanie);

//    QHBoxLayout* bytesWyswietlanie = new QHBoxLayout();
//    mainWyswietlanie->addLayout(bytesWyswietlanie);
//    QLabel* lab = new QLabel("Metoda wyswietlania:");
//    bytesWyswietlanie->addWidget(lab);
//    bytesWyswietlanie->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    kbRWyswietanie = new QComboBox();
//    kbRWyswietanie->addItems(inputsMethods);
//    connect(kbRWyswietanie, SIGNAL(currentIndexChanged(int)), this, SLOT(SendDisplayParams()));
//    bytesWyswietlanie->addWidget(kbRWyswietanie);

//    QHBoxLayout* bytesHexSign = new QHBoxLayout();
//    mainWyswietlanie->addLayout(bytesHexSign);
//    lab = new QLabel("Znacznik hex:");
//    bytesHexSign->addWidget(lab);
//    bytesHexSign->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    leRHexSign = new QLineEdit("\\");
//    leRHexSign->setInputMask("X");
//    leRHexSign->setMaximumWidth(40);
//    connect(leRHexSign, SIGNAL(textChanged(QString)), this, SLOT(SendDisplayParams()));
//    bytesHexSign->addWidget(leRHexSign);

//    QHBoxLayout* bytesInvalid = new QHBoxLayout();
//    mainWyswietlanie->addLayout(bytesInvalid);
//    lab = new QLabel("Oznaczenie nieprawidłowych znaków ASCII:");
//    bytesInvalid->addWidget(lab);
//    bytesInvalid->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    leRInvalid = new QLineEdit("?");
//    leRInvalid->setInputMask("X");
//    leRInvalid->setMaximumWidth(40);
//    connect(leRInvalid, SIGNAL(textChanged(QString)), this, SLOT(SendDisplayParams()));
//    bytesInvalid->addWidget(leRInvalid);
//}

//void LogicUITerminal::InitSend()
//{
//    QGroupBox* groupBoxWysylanie = new QGroupBox("Wysyłanie");
//    mainLay->addWidget(groupBoxWysylanie);
//    QVBoxLayout* mainWysylanie = new QVBoxLayout(groupBoxWysylanie);

//    QString tooltip = "Metoda interpretowania wprowadzanych danych do wysłania.\n"
//                      "W trybie mixed dwa kolejne znaki po wystąpieniu starteru hex\n traktowane są jako bajt zapisany hexadecymalnie, "
//                      "pozostałe\n znaki są traktowane jako ASCII. W trybie hex spacje są\n ignorowane, w pozostałych trybach są traktowane jako znak ASCII.";
//    QHBoxLayout* bytesWprowadzenia = new QHBoxLayout();
//    mainWysylanie->addLayout(bytesWprowadzenia);
//    QLabel* lab = new QLabel("Metoda wprowadzania:");
//    lab->setToolTip(tooltip);
//    bytesWprowadzenia->addWidget(lab);
//    bytesWprowadzenia->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    kbSWprowadzanie = new QComboBox();
//    kbSWprowadzanie->setToolTip(tooltip);
//    kbSWprowadzanie->addItems(inputsMethods);
//    bytesWprowadzenia->addWidget(kbSWprowadzanie);

//    tooltip = "Dwa kolejne znaki po tym symbolu zostaną odczytane jako bajt zapisany hexadecymalnie.";
//    QHBoxLayout* bytesHexSign = new QHBoxLayout();
//    mainWysylanie->addLayout(bytesHexSign);
//    lab = new QLabel("Starter hex:");
//    lab->setToolTip(tooltip);
//    bytesHexSign->addWidget(lab);
//    bytesHexSign->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
//    leSHexSign = new QLineEdit("\\");
//    leSHexSign->setToolTip(tooltip);
//    leSHexSign->setInputMask("X");
//    leSHexSign->setMaximumWidth(40);
//    bytesHexSign->addWidget(leSHexSign);

//    lab = new QLabel("Wyślij dane:");
//    mainWysylanie->addWidget(lab);

//    for(int i=0;i<6;i++)
//    {
//        Terminal_SendSection* temp = new Terminal_SendSection(mainWysylanie);
//        connect(temp, SIGNAL(Send(QString)), this, SLOT(SendData(QString)));
//        sends.push_back(temp);
//    }
//}

void LogicUIPazur::Connected()
{
//    for(int i=0;i<sends.length();i++)
//        sends[i]->Enable();
}

void LogicUIPazur::Disconnected()
{
//    for(int i=0;i<sends.length();i++)
//        sends[i]->Disable();
}

void LogicUIPazur::FrameReaded(QSharedPointer<Frame>)
{
}
