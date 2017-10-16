#include "LogicUIZR3.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>

LogicUIZR3::LogicUIZR3(QFrame* parent):
    LogicUI(parent)
{

}

void LogicUIZR3::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

    QLabel* tempLabel = new QLabel("Tu będzie coś do ZR-3");
    mainLay->addWidget(tempLabel);

    btn = new QPushButton("Wyślij coś");
    mainLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    btnE = new QPushButton("Wygeneruj bezsensowny błąd");
    mainLay->addWidget(btnE);
    connect(btnE, SIGNAL(clicked(bool)), this, SLOT(makeStupidError()));
}

void LogicUIZR3::Connected()
{
    btn->setEnabled(true);
}

void LogicUIZR3::Disconnected()
{
    btn->setEnabled(false);
}

void LogicUIZR3::FrameReaded(QSharedPointer<Frame> frame)
{
    frame.isNull();
}

void LogicUIZR3::makeStupidMessage()
{
    emit WritePureData(QByteArray("Nic nie znaczaca wiadomosc"));
}

void LogicUIZR3::makeStupidError()
{
    emit Error("Bezsensowny błąd.");
}
