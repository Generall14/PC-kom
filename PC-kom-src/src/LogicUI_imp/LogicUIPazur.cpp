#include "LogicUIPazur.hpp"
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "Frame_imp/FramePazur.hpp"
#include "Factory.hpp"
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QDebug>

LogicUIPazur::LogicUIPazur(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIPazur";
}

LogicUIPazur::~LogicUIPazur()
{
    Store("configs/LogicUIPazurleMyAdr.cfg", leMyAdr->text());
    Store("configs/LogicUIPazursbId.cfg", QString::number(sbId->value()));
    Store("configs/LogicUIPazucbFast.cfg", QString::number(cbFast->isChecked()));
    Store("configs/LogicUIPazucbIncrement.cfg", QString::number(cbIncrement->isChecked()));
}

void LogicUIPazur::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUIPazurleMyAdr.cfg", temp))
        leMyAdr->setText(temp);
    bool ok;
    int value;
    if(!Restore("configs/LogicUIPazursbId.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            sbId->setValue(value);
    }
    if(!Restore("configs/LogicUIPazucbFast.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            cbFast->setChecked(value);
    }
    if(!Restore("configs/LogicUIPazucbIncrement.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            cbIncrement->setChecked(value);
    }
}

void LogicUIPazur::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitGlobals();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void LogicUIPazur::InitGlobals()
{
    QGroupBox* groupBoxGlobalne = new QGroupBox("Globalne");
    mainLay->addWidget(groupBoxGlobalne);
    QVBoxLayout* mainGlobalne = new QVBoxLayout(groupBoxGlobalne);

    QHBoxLayout* myAdrLay = new QHBoxLayout();
    mainGlobalne->addLayout(myAdrLay);
    QLabel* lab = new QLabel("Adres nadawcy:");
    myAdrLay->addWidget(lab);
    myAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leMyAdr = new QLineEdit("FF");
    leMyAdr->setInputMask("HH");
    leMyAdr->setMaximumWidth(40);
    myAdrLay->addWidget(leMyAdr);

    QHBoxLayout* idLay = new QHBoxLayout();
    mainGlobalne->addLayout(idLay);
    lab = new QLabel("Id pakietu:");
    idLay->addWidget(lab);
    idLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    sbId = new QSpinBox();
    sbId->setMinimum(0);
    sbId->setMaximum(3);
    sbId->setValue(0);
    idLay->addWidget(sbId);
    cbIncrement = new QCheckBox("Autoinkrementacja");
    idLay->addWidget(cbIncrement);

    cbFast = new QCheckBox("Marker wymuszenia szybkiego obiegu");
    mainGlobalne->addWidget(cbFast);

    QPushButton* btn = new QPushButton("Wyślij");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Send()));
    mainGlobalne->addWidget(btn);
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
    cParent->setEnabled(true);
}

void LogicUIPazur::Disconnected()
{
    cParent->setEnabled(false);
}

void LogicUIPazur::FrameReaded(QSharedPointer<Frame>)
{
}

void LogicUIPazur::Send()
{
    uchar from = leMyAdr->text().toInt(nullptr, 16)&0x3F;
    uchar to = 0x11;
    FramePazur a(from, to, sbId->value(), cbFast->isChecked());
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(a.pureData())));
//    emit WriteFrame(QSharedPointer<Frame>(new FramePazur(from, to, sbId->value(), cbFast->isChecked())));
    if(cbIncrement->isChecked())
    {
        if(sbId->value()==sbId->maximum())
            sbId->setValue(0);
        else
            sbId->setValue(sbId->value()+1);
    }
}
