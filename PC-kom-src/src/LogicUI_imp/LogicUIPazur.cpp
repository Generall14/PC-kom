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

LogicUIPazur::LogicUIPazur(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIPazur";
}

LogicUIPazur::~LogicUIPazur()
{
    Store("configs/LogicUIPazurleMyAdr.cfg", leMyAdr->text());
    Store("configs/LogicUIPazursbId.cfg", QString::number(sbId->value()));
    Store("configs/LogicUIPazucbFast.cfg", QString::number(cbFast->isChecked()));
    Store("configs/LogicUIPazucbIncrement.cfg", QString::number(cbIncrement->isChecked()));

    delete _cfsTable;
}

void LogicUIPazur::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUIPazurleMyAdr.cfg", temp))
        leMyAdr->setText(temp);
    bool ok;
    int value;
    if(!Restore("configs/LogicUIPazursbId.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            sbId->setValue(value);
    }
    if(!Restore("configs/LogicUIPazucbFast.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            cbFast->setChecked(value);
    }
    if(!Restore("configs/LogicUIPazucbIncrement.cfg", temp))
    {
        value = temp.toInt(&ok);
        if(ok)
            cbIncrement->setChecked(value);
    }
}

void LogicUIPazur::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitGlobals();
    InitConfirms();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

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
    mainGlobalne->addWidget(cbFast);

    QPushButton* btn = new QPushButton("Wyślij");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Send()));
    mainGlobalne->addWidget(btn);
}

void LogicUIPazur::InitConfirms()
{
    QGroupBox* groupBoxPotwierdzenia = new QGroupBox("Potwierdzenia");
    mainLay->addWidget(groupBoxPotwierdzenia);
    QVBoxLayout* mainPotwierdzenia = new QVBoxLayout(groupBoxPotwierdzenia);

    QHBoxLayout* cfgsLay = new QHBoxLayout();
    mainPotwierdzenia->addLayout(cfgsLay);
    cbcfgs = new QComboBox();
    connect(cbcfgs, SIGNAL(currentIndexChanged(int)), this, SLOT(ConfsSetChanged()));
    cfgsLay->addWidget(cbcfgs);
    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ConfsAddNewSet()));
    cfgsLay->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ConfsRemoveSet()));
    cfgsLay->addWidget(btn);

    _cfsTable = new ConfsPacket(mainPotwierdzenia);
}

void LogicUIPazur::Connected()
{
    cParent->setEnabled(true);
}

void LogicUIPazur::Disconnected()
{
    cParent->setEnabled(false);
}

void LogicUIPazur::FrameReaded(QSharedPointer<Frame>)
{
}

void LogicUIPazur::Send()
{
    uchar from = leMyAdr->text().toInt(nullptr, 16)&0x3F;
    uchar to = 0x11;
    FramePazur* t = new FramePazur( from, to, sbId->value(), cbFast->isChecked(), _cfsTable->getCurrent());
    emit WriteFrame(QSharedPointer<Frame>(Factory::newFrame(t->pureData())));
    if(cbIncrement->isChecked())
    {
        if(sbId->value()==sbId->maximum())
            sbId->setValue(0);
        else
            sbId->setValue(sbId->value()+1);
    }
}

void LogicUIPazur::ConfsAddNewSet()
{
    _cfsTable->Release();

    _cfs.push_back(QList<Confirm>());
    QStringList t;
    for(int i=0;i<_cfs.size();++i)
        t.append(QString::number(i));
    cbcfgs->clear();
    cbcfgs->addItems(t);
    cbcfgs->setCurrentIndex(_cfs.size()-1);
}

void LogicUIPazur::ConfsRemoveSet()
{
    _cfsTable->Release();

    if(_cfs.isEmpty())
        return;

    int last = cbcfgs->currentIndex();
    _cfs.removeAt(last);
    QStringList t;
    for(int i=0;i<_cfs.size();++i)
        t.append(QString::number(i));
    cbcfgs->clear();
    cbcfgs->addItems(t);
    cbcfgs->setCurrentIndex(last-1);
}

void LogicUIPazur::ConfsSetChanged()
{
    _cfsTable->Release();
    if(cbcfgs->currentIndex()<0)
        return;
    if(cbcfgs->currentIndex()>=_cfs.size())
        return;

    _cfsTable->SetActive(&_cfs, cbcfgs->currentIndex());

}
