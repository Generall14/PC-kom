#include "ConfsPacket.hpp"
#include <cassert>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include "Utils/HexItemDelegate.hpp"

ConfsPacket::ConfsPacket(QBoxLayout *upperLayout)
{
    Init(upperLayout);
}

void ConfsPacket::Release()
{
    _cfs = nullptr;
    _active = -1;
    table->setRowCount(0);
    table->setEnabled(false);
    table->disconnect();
}

void ConfsPacket::SetActive(QList<QList<Confirm> > *cfs, int active)
{
    if((cfs==nullptr)||(active<0))
    {
        Release();
        return;
    }

    table->setEnabled(true);
    _cfs = cfs;
    _active = active;
    table->disconnect();

    QList<Confirm> load = (*_cfs)[_active];
    table->setRowCount(load.size());
    for(int r=0;r<load.size();++r)
    {
        char adr = 0x00;
        char id = 0x00;
        load.at(r).get(adr, id);
        QTableWidgetItem* it = new QTableWidgetItem(QString::number((uint)adr&0x3f, 16).toUpper(), 0);
        table->setItem(r, 0, it);
        it = new QTableWidgetItem(QString::number((uint)id&0x03, 16).toUpper(), 0);
        table->setItem(r, 1, it);
    }

    connect(table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(TableChanged()));
}

void ConfsPacket::Init(QBoxLayout *upperLayout)
{
    table = new QTableWidget(0, 2);
    table->setItemDelegateForColumn(0, new HexItemDelegate());
    table->setItemDelegateForColumn(1, new HexItemDelegate());
    QStringList t = {"Adres", "Id"};
    table->setHorizontalHeaderLabels(t);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    upperLayout->addWidget(table);

    QHBoxLayout* btnLay = new QHBoxLayout();
    upperLayout->addLayout(btnLay );
    QPushButton* btn = new QPushButton("Dodaj");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(AddConf()));
    btnLay ->addWidget(btn);
    btn = new QPushButton("Usuń");
//    connect(btn, SIGNAL(clicked(bool)), this, SLOT(ConfsAddRemoveConf()));
//    connect(btn, &QPushButton::clicked, [this](){twcfgs->removeRow(twcfgs->currentIndex().row());});
    btnLay ->addWidget(btn);
}

void ConfsPacket::TableChanged()
{
    if((_cfs==nullptr)||(_active<0))
        return;

    (*_cfs)[_active].clear();

    for(int r=0;r<table->rowCount();++r)
    {
        uchar adr = 0x00;
        uchar id = 0x00;
        QTableWidgetItem* it;
        it = table->item(r, 0);
        if(it!=nullptr)
            adr = it->text().left(2).toUInt(nullptr, 16);
        it = table->item(r, 1);
        if(it!=nullptr)
            id = it->text().left(2).toUInt(nullptr, 16);
        (*_cfs)[_active].append(Confirm(adr, id));
    }
}

void ConfsPacket::AddConf()
{
    table->insertRow(0);
}
