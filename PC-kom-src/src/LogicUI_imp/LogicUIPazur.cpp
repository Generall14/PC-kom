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
    Store("cbAutoConfirm", cbAutoConfirm->isChecked());

    delete _pure;
    delete _if00;
    delete _if01;
    delete _if11;
    delete _if10;
}

void LogicUIPazur::LoadConfigs()
{
    leMyAdr->setText(RestoreAsString("leMyAdr", "FF"));
    leToAdr->setText(RestoreAsString("leToAdr", "FF"));
    sbId->setValue(RestoreAsInt("sbId", 0));
    cbFast->setChecked(RestoreAsBool("cbFast", false));
    cbIncrement->setChecked(RestoreAsBool("cbIncrement", true));
    cbKwitowanie->setChecked(RestoreAsBool("cbKwitowanie", false));
    cbAutoConfirm->setChecked(RestoreAsBool("cbAutoConfirm", false));
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

//    QHBoxLayout* toAdrLay = new QHBoxLayout();
//    mainGlobalne->addLayout(toAdrLay);
    lab = new QLabel("Adres docelowy:");
    myAdrLay->addWidget(lab);
    myAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    leToAdr = new QLineEdit("FF");
    leToAdr->setInputMask("HH");
    leToAdr->setMaximumWidth(40);
    myAdrLay->addWidget(leToAdr);

    QPushButton* pbtn = new QPushButton("Wyślij pusty");
    myAdrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    connect(pbtn, &QPushButton::clicked, [this](){Send(QList<Confirm>(), QList<Message>(), cbKwitowanie->isChecked());});
    myAdrLay->addWidget(pbtn);

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

    cbAutoConfirm = new QCheckBox("Automatyczne potwierdzanie");
    mainGlobalne->addWidget(cbAutoConfirm);
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
    _if00 = new IF00(fr);
    connect(_if00, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_if00, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "IF00");

    fr = new QFrame();
    _if01 = new IF01(fr);
    connect(_if01, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_if01, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "IF01");

    fr = new QFrame();
    _if11 = new IF11ZR3(fr);
    connect(_if11, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_if11, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(this, SIGNAL(internalFrameReaded(QSharedPointer<Frame>)), _if11, SLOT(internalFrameReaded(QSharedPointer<Frame>)));
    sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "IF11ZR3");

    fr = new QFrame();
    _if10 = new IF10ZR3s(fr);
    connect(_if10, SIGNAL(Send(QList<Confirm>,QList<Message>)), this, SLOT(Send(QList<Confirm>,QList<Message>)));
    connect(_if10, SIGNAL(Error(QString)), this, SIGNAL(Error(QString)));
    connect(this, SIGNAL(internalFrameReaded(QSharedPointer<Frame>)), _if10, SLOT(internalFrameReaded(QSharedPointer<Frame>)));
    sa = new QScrollArea();
    sa->setWidget(fr);
    sa->setWidgetResizable(true);
    tw->addTab(sa, "IF10ZR3");
}

void LogicUIPazur::Connected()
{
    tw->setEnabled(true);
}

void LogicUIPazur::Disconnected()
{
    tw->setEnabled(false);
}

void LogicUIPazur::FrameReaded(QSharedPointer<Frame> fr)
{
    emit internalFrameReaded(fr);
    if(!cbAutoConfirm->isChecked())
        return;

    uchar from = leMyAdr->text().toInt(nullptr, 16)&0x3F;

    QList<Confirm> c;
    QList<Message> m;
    FramePazur paz(fr->pureData());
    bool need_to_send = false;
    for(auto m: paz.getMessages().getMessages())
    {
        char adr, ifs, x;
        QByteArray dat;
        m.get(adr, ifs, dat, x);
        if(adr==from)
        {
            c.append(Confirm(paz.srcAdr().at(0), paz.getId()));
            need_to_send = true;
        }
    }

    if(need_to_send)
        Send(c, m, true);
}

void LogicUIPazur::Send(QList<Confirm> c, QList<Message> m, bool kwitowanie)
{
    if(!kwitowanie)
        cbKwitowanie->isChecked();
    uchar from = leMyAdr->text().toInt(nullptr, 16)&0x3F;
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    FramePazur* t = new FramePazur(from, to, sbId->value(), cbFast->isChecked(), c, m, kwitowanie);
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(t->pureData())));
    if(cbIncrement->isChecked())
    {
        if(sbId->value()==sbId->maximum())
            sbId->setValue(0);
        else
            sbId->setValue(sbId->value()+1);
    }
}
