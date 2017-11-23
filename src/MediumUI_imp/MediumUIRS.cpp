#include "MediumUIRS.hpp"

#include <QLabel>
#include <QLayout>
#include <QSerialPortInfo>
#include <QStringList>
#include <QSpacerItem>
#include <QDebug>

MediumUiRS::MediumUiRS(QFrame* parent):
    MediumUI(parent)
{
    Desc::description = "MediumUiRS";
}

MediumUiRS::~MediumUiRS()
{
    Store("configs/MediumUiRSbaudrate.cfg", QString::number(speedBox->currentIndex()));
    Store("configs/MediumUiRSport.cfg", portBox->currentText());
}

void MediumUiRS::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QHBoxLayout* portSelectionLayout = new QHBoxLayout();
    mainLay->addLayout(portSelectionLayout);

    portBox = new QComboBox();
    portBox->setEditable(true);
    portSelectionLayout->addWidget(portBox);

    QStringList pred = {"1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"};
    speedBox = new QComboBox();
    speedBox->addItems(pred);
    speedBox->setCurrentIndex(4);
    portSelectionLayout->addWidget(speedBox);

    QHBoxLayout* pbLayout = new QHBoxLayout();
    mainLay->addLayout(pbLayout);

    pbLayout->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    refreshButton = new QPushButton("Odśwież");
    refreshButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pbLayout->addWidget(refreshButton);
    connect(refreshButton, SIGNAL(clicked(bool)), this, SLOT(Refresh()));

    connectButton = new QPushButton("Połącz");
    connectButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pbLayout->addWidget(connectButton);
    connect(connectButton, SIGNAL(clicked(bool)), this, SLOT(MakeConnectRequest()));

    disconnectButton = new QPushButton("Rozłącz");
    disconnectButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pbLayout->addWidget(disconnectButton);
    connect(disconnectButton, SIGNAL(clicked(bool)), this, SIGNAL(DisconnectRequest()));

    this->Refresh();
    this->Disconnected();

    LoadConfigs();
}

void MediumUiRS::LoadConfigs()
{
    QString temp;

    if(!(Restore("configs/MediumUiRSbaudrate.cfg", temp)))
        speedBox->setCurrentIndex(temp.toInt());
    if(!(Restore("configs/MediumUiRSport.cfg", temp)))
    {
        int ind = portBox->findText(temp);
        if((ind>-1)&&(ind<portBox->count()))
            portBox->setCurrentIndex(ind);
    }
}

void MediumUiRS::Refresh()
{
    portBox->clear();
    QStringList out;
    for(QSerialPortInfo l:QSerialPortInfo::availablePorts())
        out.append(l.portName());
    out.sort();
    portBox->addItems(out);
}

void MediumUiRS::MakeConnectRequest()
{
    QString temp = portBox->currentText()+";"+speedBox->currentText();
    emit ConnectRequest(temp);
    qDebug() << temp;
}

void MediumUiRS::Connected()
{
    portBox->setEnabled(false);
    speedBox->setEnabled(false);
    refreshButton->setEnabled(false);
    connectButton->setEnabled(false);
    disconnectButton->setEnabled(true);
}

void MediumUiRS::Disconnected()
{
    portBox->setEnabled(true);
    speedBox->setEnabled(true);
    refreshButton->setEnabled(true);
    connectButton->setEnabled(true);
    disconnectButton->setEnabled(false);
}
