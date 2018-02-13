#include "LogicUITerminal.hpp"
//#include <QLabel>
//#include <QLayout>
//#include <QDebug>

LogicUITerminal::LogicUITerminal(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUITerminal";
}

void LogicUITerminal::Init()
{
//    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
//    mainLay->setMargin(2);

//    QLabel* tempLabel = new QLabel("Nic tu nie ma");
//    mainLay->addWidget(tempLabel);

//    btn = new QPushButton("Wyślij coś");
//    mainLay->addWidget(btn);
//    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

//    btnE = new QPushButton("Wygeneruj bezsensowny błąd");
//    mainLay->addWidget(btnE);
//    connect(btnE, SIGNAL(clicked(bool)), this, SLOT(makeStupidError()));
}

void LogicUITerminal::Connected()
{
//    btn->setEnabled(true);
}

void LogicUITerminal::Disconnected()
{
//    btn->setEnabled(false);
}

void LogicUITerminal::FrameReaded(QSharedPointer<Frame> frame)
{
//    frame.isNull();
}

void LogicUITerminal::makeStupidMessage()
{
//    emit WritePureData(QByteArray("Nic nie znaczaca wiadomosc"));
}

void LogicUITerminal::makeStupidError()
{
//    emit Error("Bezsensowny błąd.");
}
