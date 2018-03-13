#include "LogicUITerminal.hpp"
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include "../FrameBuilder_imp/FrameBuilderTerminal.hpp"
#include "../Frame_imp/FrameTransparent.hpp"
#include <QDebug>

LogicUITerminal::LogicUITerminal(QFrame* parent):
    LogicUI(parent),
    Restorable("LogicUITerminal")
{
    Desc::description = "LogicUITerminal";
}

LogicUITerminal::~LogicUITerminal()
{
    Store("sbBytes", sbBytes->text());
    Store("leSHexSign", leSHexSign->text());
    Store("inputsMethods", kbSWprowadzanie->currentText());
    Store("kbRWyswietanie", kbRWyswietanie->currentText());
    Store("leRHexSign", leRHexSign->text());
    Store("leRInvalid", leRInvalid->text());

    for(int i=0;i<sends.length();i++)
        Store("leSend"+QString::number(i), sends.at(i)->Store());

    for(int i=0;i<sends.length();i++)
        delete sends[i];
    sends.clear();
}

void LogicUITerminal::LoadConfigs()
{
    sbBytes->setValue(RestoreAsInt("sbBytes", 10));
    leSHexSign->setText(RestoreAsString("leSHexSign", "$"));
    kbSWprowadzanie->setCurrentText(RestoreAsString("inputsMethods", ""));
    kbRWyswietanie->setCurrentText(RestoreAsString("kbRWyswietanie", ""));
    leRHexSign->setText(RestoreAsString("leRHexSign", "$"));
    leRInvalid->setText(RestoreAsString("leRInvalid", "?"));

    for(int i=0;i<sends.length();i++)
        sends.at(i)->Restore(RestoreAsString("leSend"+QString::number(i), ""));
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

    SendReceivingParams();
    SendDisplayParams();
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

    QHBoxLayout* bytesWyswietlanie = new QHBoxLayout();
    mainWyswietlanie->addLayout(bytesWyswietlanie);
    QLabel* lab = new QLabel("Metoda wyswietlania:");
    bytesWyswietlanie->addWidget(lab);
    bytesWyswietlanie->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    kbRWyswietanie = new QComboBox();
    kbRWyswietanie->addItems(inputsMethods);
    connect(kbRWyswietanie, SIGNAL(currentIndexChanged(int)), this, SLOT(SendDisplayParams()));
    bytesWyswietlanie->addWidget(kbRWyswietanie);

    QHBoxLayout* bytesHexSign = new QHBoxLayout();
    mainWyswietlanie->addLayout(bytesHexSign);
    lab = new QLabel("Znacznik hex:");
    bytesHexSign->addWidget(lab);
    bytesHexSign->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leRHexSign = new QLineEdit("$");
    leRHexSign->setInputMask("X");
    leRHexSign->setMaximumWidth(40);
    connect(leRHexSign, SIGNAL(textChanged(QString)), this, SLOT(SendDisplayParams()));
    bytesHexSign->addWidget(leRHexSign);

    QHBoxLayout* bytesInvalid = new QHBoxLayout();
    mainWyswietlanie->addLayout(bytesInvalid);
    lab = new QLabel("Oznaczenie nieprawidłowych znaków ASCII:");
    bytesInvalid->addWidget(lab);
    bytesInvalid->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leRInvalid = new QLineEdit("?");
    leRInvalid->setInputMask("X");
    leRInvalid->setMaximumWidth(40);
    connect(leRInvalid, SIGNAL(textChanged(QString)), this, SLOT(SendDisplayParams()));
    bytesInvalid->addWidget(leRInvalid);
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
    leSHexSign = new QLineEdit("$");
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
}

void LogicUITerminal::Disconnected()
{
    for(int i=0;i<sends.length();i++)
        sends[i]->Disable();
}

void LogicUITerminal::FrameReaded(QSharedPointer<Frame>)
{
}

void LogicUITerminal::SendReceivingParams()
{
    FrameBuilderTerminal::setTimeoutMs(sbTimeout->value());
    FrameBuilderTerminal::setPckSize(sbBytes->value());
}

void LogicUITerminal::SendDisplayParams()
{
    FrameTransparent::setHexSpecifier(leRHexSign->text().at(0).toLatin1());
    FrameTransparent::setInvalidAsciiSign(leRInvalid->text().at(0).toLatin1());
    FrameTransparent::setDisplayMethod((FrameTransparent::displayMethod)kbRWyswietanie->currentIndex());
}

void LogicUITerminal::SendData(QString txt)
{
    QByteArray data;
    QChar hexSign = leSHexSign->text().at(0);
    if(kbSWprowadzanie->currentText()==inputsMethods.at(0)) // ascii
    {
        data = txt.toStdString().c_str();
    }
    else if(kbSWprowadzanie->currentText()==inputsMethods.at(1)) // hex
    {
        txt.remove(' ');
        bool ok;
        int val;
        while(!txt.isEmpty())
        {
            val = txt.mid(1, 2).toInt(&ok, 16);
            if((txt.at(0)!=hexSign)||(!ok))
            {
                emit Error("Nie można odczytać danych z \"" + txt.mid(0, 3) + "\"");
                static_cast<Terminal_SendSection*>(sender())->Stop();
                return;
            }
            data.push_back((char)val);
            txt = txt.mid(3);
        }
    }
    else if(kbSWprowadzanie->currentText()==inputsMethods.at(2)) // mixed
    {
        bool ok;
        int val;
        while(!txt.isEmpty())
        {
            if(txt.at(0)==hexSign)
            {
                val = txt.mid(1, 2).toInt(&ok, 16);
                if(!ok)
                {
                    emit Error("Nie można odczytać danych z \"" + txt.mid(0, 3) + "\"");
                    static_cast<Terminal_SendSection*>(sender())->Stop();
                    return;
                }
                data.push_back((char)val);
                txt = txt.mid(3);
            }
            else
            {
                data.push_back(txt.at(0).toLatin1());
                txt = txt.mid(1);
            }
        }
    }
    else
    {
        emit Error("Coś się zepsuło");
        return;
    }
    emit WritePureData(data);
}
