#include "LogicUIEmpty.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>

LogicUIEmpty::LogicUIEmpty(QFrame* parent):
    LogicUI(parent)
{

}

void LogicUIEmpty::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(0);

    QLabel* tempLabel = new QLabel("Nic tu nie ma");
    mainLay->addWidget(tempLabel);

    btn = new QPushButton("Wyślij coś");
    mainLay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(makeStupidMessage()));

    btnE = new QPushButton("Wygeneruj bezsensowny błąd");
    mainLay->addWidget(btnE);
    connect(btnE, SIGNAL(clicked(bool)), this, SLOT(makeStupidError()));
}

void LogicUIEmpty::Connected()
{
    btn->setEnabled(true);
}

void LogicUIEmpty::Disconnected()
{
    btn->setEnabled(false);
}

void LogicUIEmpty::FrameReaded(QSharedPointer<Frame> frame)
{
    frame.isNull();
}

void LogicUIEmpty::makeStupidMessage()
{
    emit WritePureData(QByteArray("Nic nie znaczaca wiadomosc"));
}

void LogicUIEmpty::makeStupidError()
{
    emit Error("Bezsensowny błąd.");
}
