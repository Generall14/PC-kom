#include "LogicUITerminal.hpp"
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include "../FrameBuilder_imp/FrameBuilderTerminal.hpp"
//#include <QLayout>
//#include <QDebug>

LogicUITerminal::LogicUITerminal(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUITerminal";
}

LogicUITerminal::~LogicUITerminal()
{
    Store("configs/LogicUITerminalsbBytes.cfg", sbBytes->text());
    Store("configs/LogicUITerminalleSHexSign.cfg", leSHexSign->text());
    Store("configs/LogicUITerminalinputsMethods.cfg", kbSWprowadzanie->currentText());
//    Store("configs/LogicUIStawrovmetrozniczkowanie.cfg", QString::number((int)rozniczkowanie->isChecked()));

    for(int i=0;i<sends.length();i++)
        Store("configs/LogicUITerminalleSend"+QString::number(i)+".cfg", sends.at(i)->Store());

    for(int i=0;i<sends.length();i++)
        delete sends[i];
    sends.clear();
}

void LogicUITerminal::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUITerminalleSHexSign.cfg", temp))
        leSHexSign->setText(temp);
    if(!Restore("configs/LogicUITerminalinputsMethods.cfg", temp))
        kbSWprowadzanie->setCurrentText(temp);
    if(!Restore("configs/LogicUITerminalsbBytes.cfg", temp))
    {
        bool ok;
        int vale = temp.toInt(&ok);
        if(ok)
            sbBytes->setValue(vale);
    }
    for(int i=0;i<sends.length();i++)
    {
        if(!Restore("configs/LogicUITerminalleSend"+QString::number(i)+".cfg", temp))
            sends.at(i)->Restore(temp);
    }
}

void LogicUITerminal::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitReceive();
    InitDisplay();
    InitSend();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
}

void LogicUITerminal::InitReceive()
{
    QString tooltip = "Dane będą wyświetlone gdy zostanie uzbierana odpowiednia ilość bajtów lub upłynie timeout od odebrania pierwszego bajtu w pakiecie";

    QGroupBox* groupBoxOdbieranie = new QGroupBox("Odbieranie");
    groupBoxOdbieranie->setToolTip(tooltip);
    mainLay->addWidget(groupBoxOdbieranie);
    QVBoxLayout* mainOdbieranie = new QVBoxLayout(groupBoxOdbieranie);

    QHBoxLayout* bytesLay = new QHBoxLayout();
    mainOdbieranie->addLayout(bytesLay);
    QLabel* lab = new QLabel("Bajtów w pakiecie:");
    bytesLay->addWidget(lab);
    bytesLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    sbBytes = new QSpinBox();
    sbBytes->setMinimum(1);
    sbBytes->setMaximum(50);
    sbBytes->setValue(10);
    connect(sbBytes, SIGNAL(valueChanged(int)), this, SLOT(SendReceivingParams()));
    bytesLay->addWidget(sbBytes);

    QHBoxLayout* timeoutLay = new QHBoxLayout();
    mainOdbieranie->addLayout(timeoutLay);
    lab = new QLabel("Timeout pakietu [ms]:");
    timeoutLay->addWidget(lab);
    timeoutLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    sbTimeout = new QSpinBox();
    sbTimeout->setMinimum(10);
    sbTimeout->setMaximum(5000);
    sbTimeout->setValue(100);
    connect(sbTimeout, SIGNAL(valueChanged(int)), this, SLOT(SendReceivingParams()));
    timeoutLay->addWidget(sbTimeout);
}

void LogicUITerminal::InitDisplay()
{
    QGroupBox* groupBoxWyswietlanie = new QGroupBox("Wyświetlanie");
    mainLay->addWidget(groupBoxWyswietlanie);
    QVBoxLayout* mainWyswietlanie = new QVBoxLayout(groupBoxWyswietlanie);
}

void LogicUITerminal::InitSend()
{
    QGroupBox* groupBoxWysylanie = new QGroupBox("Wysyłanie");
    mainLay->addWidget(groupBoxWysylanie);
    QVBoxLayout* mainWysylanie = new QVBoxLayout(groupBoxWysylanie);

    QString tooltip = "Metoda interpretowania wprowadzanych danych do wysłania.\n"
                      "W trybie mixed dwa kolejne znaki po wystąpieniu starteru hex\n traktowane są jako bajt zapisany hexadecymalnie, "
                      "pozostałe\n znaki są traktowane jako ASCII. W trybie hex spacje są\n ignorowane, w pozostałych trybach są traktowane jako znak ASCII.";
    QHBoxLayout* bytesWprowadzenia = new QHBoxLayout();
    mainWysylanie->addLayout(bytesWprowadzenia);
    QLabel* lab = new QLabel("Metoda wprowadzania:");
    lab->setToolTip(tooltip);
    bytesWprowadzenia->addWidget(lab);
    bytesWprowadzenia->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    kbSWprowadzanie = new QComboBox();
    kbSWprowadzanie->setToolTip(tooltip);
    kbSWprowadzanie->addItems(inputsMethods);
    bytesWprowadzenia->addWidget(kbSWprowadzanie);

    tooltip = "Dwa kolejne znaki po tym symbolu zostaną odczytane jako bajt zapisany hexadecymalnie.";
    QHBoxLayout* bytesHexSign = new QHBoxLayout();
    mainWysylanie->addLayout(bytesHexSign);
    lab = new QLabel("Starter hex:");
    lab->setToolTip(tooltip);
    bytesHexSign->addWidget(lab);
    bytesHexSign->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leSHexSign = new QLineEdit("\\");
    leSHexSign->setToolTip(tooltip);
    leSHexSign->setInputMask("X");
    leSHexSign->setMaximumWidth(40);
    bytesHexSign->addWidget(leSHexSign);

    lab = new QLabel("Wyślij dane:");
    mainWysylanie->addWidget(lab);

    for(int i=0;i<6;i++)
    {
        Terminal_SendSection* temp = new Terminal_SendSection(mainWysylanie);
        connect(temp, SIGNAL(Send(QString)), this, SLOT(SendData(QString)));
        sends.push_back(temp);
    }
}

void LogicUITerminal::Connected()
{
    for(int i=0;i<sends.length();i++)
        sends[i]->Enable();
//    btn->setEnabled(true);
}

void LogicUITerminal::Disconnected()
{
    for(int i=0;i<sends.length();i++)
        sends[i]->Disable();
//    btn->setEnabled(false);
}

void LogicUITerminal::FrameReaded(QSharedPointer<Frame>)
{
//    frame.isNull();
}

void LogicUITerminal::SendReceivingParams()
{
    FrameBuilderTerminal::setTimeoutMs(sbTimeout->value());
    FrameBuilderTerminal::setPckSize(sbBytes->value());
}

void LogicUITerminal::SendData(QString txt)
{
    QByteArray data;
    if(kbSWprowadzanie->currentText()==inputsMethods.at(0)) // ascii
    {
        data = txt.toStdString().c_str();
    }
    else if(kbSWprowadzanie->currentText()==inputsMethods.at(1)) // hex
    {
        if(txt.at(0)=='a')
        {
            static_cast<Terminal_SendSection*>(sender())->Stop();
            emit Error("Coś się zepsuło");
        }
    }
    else if(kbSWprowadzanie->currentText()==inputsMethods.at(2)) // mixed
    {

    }
    else
    {
        emit Error("Coś się zepsuło");
        return;
    }
    emit WritePureData(data);
}
