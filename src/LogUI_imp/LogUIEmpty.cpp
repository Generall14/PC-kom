#include "LogUIEmpty.hpp"
#include <QLayout>
#include <QDebug>
#include "../Factory.hpp"

LogUIEmpty::LogUIEmpty(QFrame* parent):
    LogUI(parent)
{

}

void LogUIEmpty::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);

    mainLay->addWidget(new QLabel("Prymitywny log. Ostatnie dane:"));

    inLabel = new QLabel();
    mainLay->addWidget(inLabel);

    outLabel = new QLabel();
    mainLay->addWidget(outLabel);
}

void LogUIEmpty::FrameWrite(QSharedPointer<Frame> frame)
{
    qDebug() << "Logowanie zapisu";
    outLabel->setText("Out: "+frame->toQString());
    emit LogString(frame->toQString());
}

void LogUIEmpty::FrameReaded(QSharedPointer<Frame> frame)
{
    qDebug() << "Logowanie odczytu";
    inLabel->setText("In: "+frame->toQString());
    emit LogString(frame->toQString());
}
