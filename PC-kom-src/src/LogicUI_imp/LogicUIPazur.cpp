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

LogicUIPazur::LogicUIPazur(QFrame* parent):
    LogicUI(parent)
{
    Desc::description = "LogicUIPazur";
}

LogicUIPazur::~LogicUIPazur()
{
    Store("configs/LogicUIPazurleMyAdr.cfg", leMyAdr->text());
    Store("configs/LogicUIPazurleToAdr.cfg", leToAdr->text());
    Store("configs/LogicUIPazursbId.cfg", QString::number(sbId->value()));
    Store("configs/LogicUIPazucbFast.cfg", QString::number(cbFast->isChecked()));
    Store("configs/LogicUIPazucbIncrement.cfg", QString::number(cbIncrement->isChecked()));

    StoreLists();

    delete _cfsTable;
    delete _msgTable;
}

void LogicUIPazur::LoadConfigs()
{
    QString temp;

    if(!Restore("configs/LogicUIPazurleMyAdr.cfg", temp))
        leMyAdr->setText(temp);
    if(!Restore("configs/LogicUIPazurleToAdr.cfg", temp))
        leToAdr->setText(temp);
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
    InitMessages();

    mainLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding, QSizePolicy::Expanding));

    LoadConfigs();
    RestoreLists();
    ConfsReload();
    MsgReload();
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

void LogicUIPazur::InitMessages()
{
    QGroupBox* groupBoxKomunikaty = new QGroupBox("Komunikaty");
    mainLay->addWidget(groupBoxKomunikaty);
    QVBoxLayout* mainKomunikaty = new QVBoxLayout(groupBoxKomunikaty);

    QHBoxLayout* msgsLay = new QHBoxLayout();
    mainKomunikaty->addLayout(msgsLay);
    cbmsgs = new QComboBox();
    connect(cbmsgs, SIGNAL(currentIndexChanged(int)), this, SLOT(MsgSetChanged()));
    msgsLay->addWidget(cbmsgs);
    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(MsgAddNewSet()));
    msgsLay->addWidget(btn);
    btn = new QPushButton("Usuń");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(MsgRemoveSet()));
    msgsLay->addWidget(btn);

    _msgTable = new MsgPacket(mainKomunikaty);
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
    uchar to = leToAdr->text().toInt(nullptr, 16)&0x3F;
    FramePazur* t = new FramePazur( from, to, sbId->value(), cbFast->isChecked(), _cfsTable->getCurrent(), _msgTable->getCurrent() );
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

    ConfsReload();
}

void LogicUIPazur::ConfsReload()
{
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
    ConfsReload();
    if((last==0)&&(cbcfgs->count()>0))
        last = 1;
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

void LogicUIPazur::MsgAddNewSet()
{
    _msgTable->Release();

    _msgs.push_back(QList<Message>());
    MsgReload();
}

void LogicUIPazur::MsgReload()
{
    QStringList t;
    for(int i=0;i<_msgs.size();++i)
        t.append(QString::number(i));
    cbmsgs->clear();
    cbmsgs->addItems(t);
    cbmsgs->setCurrentIndex(_msgs.size()-1);
}

void LogicUIPazur::MsgRemoveSet()
{
    _msgTable->Release();

    if(_msgs.isEmpty())
        return;

    int last = cbmsgs->currentIndex();
    _msgs.removeAt(last);
    MsgReload();
    if((last==0)&&(cbmsgs->count()>0))
        last = 1;
    cbmsgs->setCurrentIndex(last-1);
}

void LogicUIPazur::MsgSetChanged()
{
    _msgTable->Release();
    if(cbmsgs->currentIndex()<0)
        return;
    if(cbmsgs->currentIndex()>=_msgs.size())
        return;

    _msgTable->SetActive(&_msgs, cbmsgs->currentIndex());
}

void LogicUIPazur::StoreLists()
{
    pugi::xml_document* xmldoc = GlobalXmlFile::get().root();

    xmldoc->remove_child("Confirm-store");
    xmldoc->remove_child("Message-store");

    pugi::xml_node confsnode = xmldoc->append_child("Confirm-store");
    for(int i=0;i<_cfs.size();++i)
    {
        QList<Confirm> list = _cfs.at(i);
        pugi::xml_node listnode = confsnode.append_child(QString("list_"+QString::number(i)).toStdString().c_str());
        for(int l=0;l<list.size();l++)
        {
            char adr, id;
            Confirm c = list.at(l);
            c.get(adr, id);
            pugi::xml_node cnfnode = listnode.append_child(QString("confirm_"+QString::number(l)).toStdString().c_str());
            cnfnode.append_attribute("adr") = adr;
            cnfnode.append_attribute("id") = id;
        }
    }

    pugi::xml_node msgnode = xmldoc->append_child("Message-store");
    for(int i=0;i<_msgs.size();++i)
    {
        QList<Message> list = _msgs.at(i);
        pugi::xml_node listnode = msgnode.append_child(QString("list_"+QString::number(i)).toStdString().c_str());
        for(int l=0;l<list.size();l++)
        {
            char adr, ifs, x;
            QByteArray dat;
            Message m = list.at(l);
            m.get(adr, ifs, dat, x);
            QString str;
            for(auto a: dat)
                str.append(QString::number((uint)a&0xFF, 16).toUpper()+" ");
            pugi::xml_node msgnode = listnode.append_child(QString("message_"+QString::number(l)).toStdString().c_str());
            msgnode.append_attribute("adr") = adr;
            msgnode.append_attribute("ifs") = ifs;
            msgnode.append_attribute("x") = x;
            msgnode.append_attribute("dat") = str.toStdString().c_str();
        }
    }
}

void LogicUIPazur::RestoreLists()
{
    pugi::xml_document* xmldoc = GlobalXmlFile::get().root();
    qDebug() << xmldoc->text().as_string();

    pugi::xml_node confsnode = xmldoc->child("Confirm-store");
    if(!confsnode.empty())
    {
        for(pugi::xml_node_iterator lit = confsnode.begin(); lit != confsnode.end(); ++lit)
        {
            QList<Confirm> list;
            for(pugi::xml_node_iterator cit = lit->begin(); cit != lit->end(); ++cit)
            {
                char adr, id;
                adr = cit->attribute("adr").as_uint();
                id = cit->attribute("id").as_uint();
                Confirm c(adr, id);
                list.push_back(c);
            }
            _cfs.push_back(list);
        }
    }

    pugi::xml_node msgsnode = xmldoc->child("Message-store");
    if(!msgsnode.empty())
    {
        for(pugi::xml_node_iterator lit = msgsnode.begin(); lit != msgsnode.end(); ++lit)
        {
            QList<Message> list;
            for(pugi::xml_node_iterator mit = lit->begin(); mit != lit->end(); ++mit)
            {
                qDebug() << mit->text().as_string();
                char adr, ifs, x;
                QByteArray dat;
                QString str;
                adr = mit->attribute("adr").as_uint();
                ifs = mit->attribute("ifs").as_uint();
                x = mit->attribute("x").as_uint();
                str = mit->attribute("dat").as_string();
                str.remove(' ');
                bool ok;
                int val;
                while(!str.isEmpty())
                {
                    val = str.left(2).toInt(&ok, 16);
                    if(ok)
                        dat.push_back((char)val);
                    str = str.mid(2);
                }
                Message m(adr, ifs, dat, x);
                list.push_back(m);
            }
            _msgs.push_back(list);
        }
    }
}
