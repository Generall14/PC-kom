#include "LogicUISProt.hpp"
#include <QLabel>
#include <QLayout>
#include <QDebug>
#include <QGroupBox>
#include <QSpacerItem>
#include "utils_SProt/SProtPure.hpp"

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

    pureFrame = new QFrame();
    tw->addTab(pureFrame, "Pure");
    auto tabPure = QSharedPointer<LogicUI>(new SProtPure(pureFrame));
    tabs.append(tabPure);

    for(QSharedPointer<LogicUI> tab: tabs)
    {
        connect(this, &LogicUISProt::iConnected, tab.data(), &LogicUI::Connected);
        connect(this, &LogicUISProt::iDisconnected, tab.data(), &LogicUI::Disconnected);
        connect(this, &LogicUISProt::iFrameReaded, tab.data(), &LogicUI::FrameReaded);
        connect(tab.data(), &LogicUI::WriteFrame, this, &LogicUISProt::WriteFrame);
        connect(tab.data(), &LogicUI::WritePureData, this, &LogicUISProt::WritePureData);

        tab->Init();
    }
    Disconnected();
}

void LogicUISProt::Connected()
{
    emit iConnected();
}

void LogicUISProt::Disconnected()
{
    emit iDisconnected();
}

void LogicUISProt::FrameReaded(QSharedPointer<Frame> frame)
{
    emit iFrameReaded(frame);
}
