#include "ZR3UIFrame.hpp"
#include <QLayout>
#include "../../Frame_imp/FrameZR3.hpp"
#include "../../Factory.hpp"

ZR3UIFrame::ZR3UIFrame(QFrame* parent, uchar adr):
    QObject(parent),
    cFrame(parent),
    _adr(adr)
{
    protHELLO.append(0xFF);
    protHELLO.append(0x01);
    protHELLO.append(_adr);
    protHELLO.append(_myAdr);
    protHELLO.append((char)0x00);
    FrameZR3::AppendLRC(protHELLO);
}

void ZR3UIFrame::Init()
{
    QVBoxLayout* mainLay = new QVBoxLayout(cFrame);
    mainLay->setMargin(1);

    QTabWidget* qtw = new QTabWidget();
    qtw->setTabPosition(QTabWidget::South);
    mainLay->addWidget(qtw);

    dbgFrame = new QFrame();
    qtw->addTab(dbgFrame, "Debug");

    suiFrame = new QFrame();
    qtw->addTab(suiFrame, "Simple UI");

    InitDebug();
}

void ZR3UIFrame::InitDebug()
{
    QVBoxLayout* mainLay = new QVBoxLayout(dbgFrame);
    mainLay->setMargin(6);

    QPushButton* btnHello = new QPushButton("protHELLO");
    connect(btnHello, &QPushButton::clicked, [=](){emit FrameToMendium(QSharedPointer<Frame>(Factory::newFrame(protHELLO)));});
    mainLay->addWidget(btnHello);
}

void ZR3UIFrame::FrameToUI(QSharedPointer<Frame> frame)
{

}

uchar ZR3UIFrame::Adr() const
{
    return _adr;
}
