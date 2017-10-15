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
    mainLay->setMargin(0);

    mainLay->addWidget(new QLabel("Prymitywny log. Ostatnie dane:"));

    inLabel = new QLabel();
    mainLay->addWidget(inLabel);

    outLabel = new QLabel();
    mainLay->addWidget(outLabel);
}

void LogUIEmpty::LogString(QString str, bool dirin)
{
    if(dirin)
        inLabel->setText(str);
    else
        outLabel->setText(str);
}
