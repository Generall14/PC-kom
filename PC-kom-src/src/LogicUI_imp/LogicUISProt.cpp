#include "LogicUISProt.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGroupBox>
#include <QSpacerItem>
#include "utils_SG1/DataCollector.hpp"
#include "utils_SG1/WorkerRead.hpp"
#include "utils_SG1/WorkerWrite.hpp"
#include "utils_SG1/Worker.hpp"
#include "utils_SG1/WorkerManager.hpp"

LogicUISProt::LogicUISProt(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUISProt";

//    while(data.size()<128)
//        data.append((char)(0x00));
}

void LogicUISProt::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QTabWidget* tw = new QTabWidget();
    mainLay->addWidget(tw);

//    errorLabel = new QLabel("");
//    standardPalette = errorLabel->palette();
//    errorPalette = standardPalette;
//    errorPalette.setColor(QPalette::WindowText, Qt::black);
//    errorPalette.setColor(QPalette::Window, Qt::red);
//    errorLabel->setAutoFillBackground(true);
//    cParent->setAutoFillBackground(true);
//    mainLay->addWidget(errorLabel);

//    dbgFrame = new QFrame();
//    tw->addTab(dbgFrame, "Debug");
//    InitDebug();

//    calFrame = new QFrame();
//    tw->addTab(calFrame, "Kalibracja");
//    InitCal();
}

void LogicUISProt::Connected()
{
//    dbgFrame->setEnabled(true);
//    calFrame->setEnabled(true);
}

void LogicUISProt::Disconnected()
{
//    dbgFrame->setEnabled(false);
//    calFrame->setEnabled(false);
}

void LogicUISProt::FrameReaded(QSharedPointer<Frame> frame)
{

}
