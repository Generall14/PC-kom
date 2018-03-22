#include "Pure.hpp"
#include <QGroupBox>
#include <QScrollArea>

Pure::Pure(QFrame* parent):
    Restorable("LogicUIPazur"),
    cParent(parent)
{
    Init();
}

Pure::~Pure()
{
    StoreLists();

    delete _cfsTable;
    delete _msgTable;
}

void Pure::Init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    InitConfirms();
    InitMessages();

    RestoreLists();
    ConfsReload();
    MsgReload();

    QPushButton* btn = new QPushButton("Wyślij");
    connect(btn, &QPushButton::clicked, [this](){emit Send(_cfsTable->getCurrent(), _msgTable->getCurrent());});
    mainLay->addWidget(btn);
}

void Pure::InitConfirms()
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

void Pure::InitMessages()
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

void Pure::ConfsAddNewSet()
{
    _cfsTable->Release();

    _cfs.push_back(QList<Confirm>());

    ConfsReload();
}

void Pure::ConfsReload()
{
    QStringList t;
    for(int i=0;i<_cfs.size();++i)
        t.append(QString::number(i));
    cbcfgs->clear();
    cbcfgs->addItems(t);
    cbcfgs->setCurrentIndex(_cfs.size()-1);
}

void Pure::ConfsRemoveSet()
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

void Pure::ConfsSetChanged()
{
    _cfsTable->Release();
    if(cbcfgs->currentIndex()<0)
        return;
    if(cbcfgs->currentIndex()>=_cfs.size())
        return;

    _cfsTable->SetActive(&_cfs, cbcfgs->currentIndex());
}

void Pure::MsgAddNewSet()
{
    _msgTable->Release();

    _msgs.push_back(QList<Message>());
    MsgReload();
}

void Pure::MsgReload()
{
    QStringList t;
    for(int i=0;i<_msgs.size();++i)
        t.append(QString::number(i));
    cbmsgs->clear();
    cbmsgs->addItems(t);
    cbmsgs->setCurrentIndex(_msgs.size()-1);
}

void Pure::MsgRemoveSet()
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

void Pure::MsgSetChanged()
{
    _msgTable->Release();
    if(cbmsgs->currentIndex()<0)
        return;
    if(cbmsgs->currentIndex()>=_msgs.size())
        return;

    _msgTable->SetActive(&_msgs, cbmsgs->currentIndex());
}

void Pure::StoreLists()
{
    GlobalXmlFile::getMainNode().remove_child("Confirm-store");
    GlobalXmlFile::getMainNode().remove_child("Message-store");

    pugi::xml_node confsnode = GlobalXmlFile::getMainNode().append_child("Confirm-store");
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

    pugi::xml_node msgnode = GlobalXmlFile::getMainNode().append_child("Message-store");
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
                str.append(QString("%1 ").arg((uint)a&0xFF, 2, 16, QChar('0')));
            pugi::xml_node msgnode = listnode.append_child(QString("message_"+QString::number(l)).toStdString().c_str());
            msgnode.append_attribute("adr") = adr;
            msgnode.append_attribute("ifs") = ifs;
            msgnode.append_attribute("x") = x;
            msgnode.append_attribute("dat") = str.toStdString().c_str();
        }
    }
}

void Pure::RestoreLists()
{
    pugi::xml_node confsnode = GlobalXmlFile::getMainNode().child("Confirm-store");
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

    pugi::xml_node msgsnode = GlobalXmlFile::getMainNode().child("Message-store");
    if(!msgsnode.empty())
    {
        for(pugi::xml_node_iterator lit = msgsnode.begin(); lit != msgsnode.end(); ++lit)
        {
            QList<Message> list;
            for(pugi::xml_node_iterator mit = lit->begin(); mit != lit->end(); ++mit)
            {
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
