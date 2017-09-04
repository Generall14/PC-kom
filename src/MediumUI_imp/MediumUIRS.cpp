#include "MediumUIRS.hpp"

#include <QLabel>
#include <QLayout>
#include <QSerialPortInfo>
#include <QStringList>
#include <QSpacerItem>

MediumUiRS::MediumUiRS(QFrame* parent):
    MediumUI(parent)
{

}

void MediumUiRS::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

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
}

void MediumUiRS::Refresh()
{
    portBox->clear();
    for(auto pi: QSerialPortInfo::availablePorts())
        portBox->addItem(pi.portName());
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
