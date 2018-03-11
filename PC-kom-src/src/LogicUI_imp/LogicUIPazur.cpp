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
//    connect(btn, SIGNAL(clicked(bool)), this, SLOT(Send()));
    cfgsLay->addWidget(btn);

//    twcfgs = new QTableWidget(0, 2);
//    QStringList t = {"Adres", "Id"};
//    twcfgs->setHorizontalHeaderLabels(t);
//    twcfgs->setSelectionMode(QAbstractItemView::SingleSelection);
//    twcfgs->setSelectionBehavior(QAbstractItemView::SelectRows);
//    mainPotwierdzenia->addWidget(twcfgs);

//    QHBoxLayout* tabcfgsLay = new QHBoxLayout();
//    mainPotwierdzenia->addLayout(tabcfgsLay);
//    btn = new QPushButton("Dodaj");
//    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ConfsAddNewConf()));
//    tabcfgsLay->addWidget(btn);
//    btn = new QPushButton("Usuń");
////    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ConfsAddRemoveConf()));
//    connect(btn, &QPushButton::clicked, [this](){twcfgs->removeRow(twcfgs->currentIndex().row());});
//    tabcfgsLay->addWidget(btn);

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
    emit WriteFrame(QSharedPointer<Frame>(new FramePazur(from, to, sbId->value(), cbFast->isChecked())));
    if(cbIncrement->isChecked())
    {
        if(sbId->value()==sbId->maximum())
            sbId->setValue(0);
        else
            sbId->setValue(sbId->value()+1);
    }
}

//Confs:
void LogicUIPazur::ConfStoreCurrent()
{
//piach?
}

void LogicUIPazur::ConfsAddNewSet()
{
//    ConfStoreCurrent();
    _cfsTable->Release();

    _cfs.push_back(QList<Confirm>());
    QStringList t;
    for(int i=0;i<_cfs.size();++i)
        t.append(QString::number(i));
    cbcfgs->clear();
    cbcfgs->addItems(t);
    currentConf = _cfs.size()-1;
    cbcfgs->setCurrentIndex(currentConf);
}

void LogicUIPazur::ConfsAddNewConf()
{
//    twcfgs->insertRow(0);
//    QLineEdit* edit = new QLineEdit(twcfgs);
//    edit->setValidator(new HexValidator(1, 1));
//    twcfgs->setCellWidget(0, 0, edit);
//    edit = new QLineEdit(twcfgs);
//    edit->setValidator(new HexValidator(1, 1));
//    twcfgs->setCellWidget(0, 1, edit);
}

void LogicUIPazur::ConfsSetChanged()
{
    _cfsTable->Release();
    if(cbcfgs->currentIndex()<0)
        return;
    if(cbcfgs->currentIndex()>=_cfs.size())
        return;

//    QList<Confirm> *a = &(_cfs.at(cbcfgs->currentIndex()));
    _cfsTable->SetActive(&_cfs, cbcfgs->currentIndex());

    //store


//    currentConf = cbcfgs->currentIndex();
//    if(currentConf<0)
//    {
//        twcfgs->setRowCount(0);
//        twcfgs->setEnabled(false);
//        return;
//    }

//    twcfgs->setEnabled(true);
}
