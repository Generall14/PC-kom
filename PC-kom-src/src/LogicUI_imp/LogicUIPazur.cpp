#include "LogicUIPazur.hpp"
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "Frame_imp/FramePazur.hpp"
#include "Factory.hpp"
#include <QGroupBox>
#include <QLabel>
#include <QToolButton>
#include <QPushButton>
#include <QDebug>
#include "Utils/ValidateHex.hpp"
#include "Utils/pugixml.hpp"
#include "Utils/GlobalXmlFile.hpp"
#include <QScrollArea>

LogicUIPazur::LogicUIPazur(QFrame* parent):
    LogicUI(parent),
    Restorable("LogicUIPazur")
{
    Desc::description = "LogicUIPazur";
}

LogicUIPazur::~LogicUIPazur()
{
    Store("leMyAdr", leMyAdr->text());
    Store("leToAdr", leToAdr->text());
    Store("sbId", sbId->value());
    Store("cbFast", cbFast->isChecked());
    Store("cbIncrement", cbIncrement->isChecked());
    Store("cbKwitowanie", cbKwitowanie->isChecked());

    delete _pure;
    delete _if01;
}

void LogicUIPazur::LoadConfigs()
{
    leMyAdr->setText(RestoreAsString("leMyAdr", "FF"));
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    sbId->setValue(RestoreAsInt("sbId", 0));
    cbFast->setChecked(RestoreAsBool("cbFast", false));
    cbIncrement->setChecked(RestoreAsBool("cbIncrement", true));
    cbKwitowanie->setChecked(RestoreAsBool("cbKwitowanie", false));
}

void LogicUIPazur::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitGlobals();
    InitTabs();

    LoadConfigs();
}

void LogicUIPazur::InitGlobals()
{
    QGroupBox* groupBoxGlobalne = new QGroupBox("Globalne");
    mainLay->addWidget(groupBoxGlobalne);
    QVBoxLayout* mainGlobalne = new QVBoxLayout(groupBoxGlobalne);

    QHBoxLayout* myAdrLay = new QHBoxLayout();
    mainGlobalne->addLayout(myAdrLay);
    QLabel* lab = new QLabel("Adres nadawcy:");
    myAdrLay->addWidget(lab);
    myAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leMyAdr = new QLineEdit("FF");
    leMyAdr->setInputMask("HH");
    leMyAdr->setMaximumWidth(40);
    myAdrLay->addWidget(leMyAdr);

    QHBoxLayout* toAdrLay = new QHBoxLayout();
    mainGlobalne->addLayout(toAdrLay);
    lab = new QLabel("Adres docelowy:");
    toAdrLay->addWidget(lab);
    toAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    toAdrLay->addWidget(leToAdr);

    QHBoxLayout* idLay = new QHBoxLayout();
    mainGlobalne->addLayout(idLay);
    lab = new QLabel("Id pakietu:");
    idLay->addWidget(lab);
    idLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    sbId = new QSpinBox();
    sbId->setMinimum(0);
    sbId->setMaximum(3);
    sbId->setValue(0);
    idLay->addWidget(sbId);
    cbIncrement = new QCheckBox("Autoinkrementacja");
    idLay->addWidget(cbIncrement);

    cbFast = new QCheckBox("Marker wymuszenia szybkiego obiegu");
    cbFast->setMinimumWidth(350);
    mainGlobalne->addWidget(cbFast);

    cbKwitowanie = new QCheckBox("Kwitowanie");
    mainGlobalne->addWidget(cbKwitowanie);
}

void LogicUIPazur::InitTabs()
{
    tw = new QTabWidget();
    tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLay->addWidget(tw);

    QFrame* fr = new QFrame();
    _pure = new Pure(fr);
    connect(_pure, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_pure, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    QScrollArea* sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "Pure");

    fr = new QFrame();
    _if01 = new IF01(fr);
    connect(_if01, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_if01, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "IF01");
}

void LogicUIPazur::Connected()
{
    tw->setEnabled(true);
}

void LogicUIPazur::Disconnected()
{
    tw->setEnabled(false);
}

void LogicUIPazur::FrameReaded(QSharedPointer<Frame>)
{
}

void LogicUIPazur::Send(QList<Confirm> c, QList<Message> m)
{
    uchar from = leMyAdr->text().toInt(nullptr, 16)&0x3F;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    FramePazur* t = new FramePazur( from, to, sbId->value(), cbFast->isChecked(), c, m, cbKwitowanie->isChecked());
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(t->pureData())));
    if(cbIncrement->isChecked())
    {
        if(sbId->value()==sbId->maximum())
            sbId->setValue(0);
        else
            sbId->setValue(sbId->value()+1);
    }
}
