#include "MsgPacket.hpp"
#include <cassert>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QStyledItemDelegate>
#include "Utils/HexItemDelegate.hpp"

MsgPacket::MsgPacket(QBoxLayout *upperLayout)
{
    Init(upperLayout);
    Release();
}

void MsgPacket::Release()
{
    _mags = nullptr;
    _active = -1;
    table->setRowCount(0);
    table->setEnabled(false);
    btnd->setEnabled(false);
    btnu->setEnabled(false);
    table->disconnect();
}

QList<Message> MsgPacket::getCurrent()
{
    if((_mags==nullptr)||(_active<0))
        return QList<Message>();
    QList<Message> load = (*_mags)[_active];
    return load;
}

void MsgPacket::SetActive(QList<QList<Message> > *msg, int active)
{
    if((msg==nullptr)||(active<0))
    {
        Release();
        return;
    }

    table->setEnabled(true);
    btnd->setEnabled(true);
    btnu->setEnabled(true);
    _mags = msg;
    _active = active;
    table->disconnect();

    QList<Message> load = (*_mags)[_active];
    table->setRowCount(load.size());
    for(int r=0;r<load.size();++r)
    {
        char adr = 0x00;
        char in = 0x00;
        char x = 0x00;
        QByteArray dat;
        load.at(r).get(adr, in, dat, x);

        QTableWidgetItem* it = new QTableWidgetItem(QString::number((uint)adr&0x3f, 16).toUpper(), 0);
        table->setItem(r, 0, it);

        it = new QTableWidgetItem(QString::number((uint)in&0x03, 16).toUpper(), 0);
        table->setItem(r, 1, it);

        it = new QTableWidgetItem(QString::number((uint)x&0x03, 16).toUpper(), 0);
        table->setItem(r, 2, it);

        QString str;
        for(auto a: dat)
            str.append(QString::number((uint)a&0xFF, 16).toUpper()+" ");
        it = new QTableWidgetItem(str, 0);
        table->setItem(r, 3, it);
    }

    connect(table, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(TableChanged()));

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

void MsgPacket::Init(QBoxLayout *upperLayout)
{
    table = new QTableWidget(0, 4);
    table->setItemDelegateForColumn(0, new HexItemDelegate(1, 1));
    table->setItemDelegateForColumn(1, new HexItemDelegate(1, 1));
    table->setItemDelegateForColumn(2, new HexItemDelegate(1, 1));
    table->setItemDelegateForColumn(3, new HexItemDelegate());
    QStringList t = {"Adr", "If", "X", "Dane"};
    table->setHorizontalHeaderLabels(t);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    upperLayout->addWidget(table);

    QHBoxLayout* btnLay = new QHBoxLayout();
    upperLayout->addLayout(btnLay );
    btnd = new QPushButton("Dodaj");
    connect(btnd, &QPushButton::clicked, [this](){table->insertRow(0);});
    btnLay ->addWidget(btnd);
    btnu = new QPushButton("Usuń");
    connect(btnu, SIGNAL(clicked(bool)), this, SLOT(RemoveMsg()));
    btnLay ->addWidget(btnu);
}

void MsgPacket::TableChanged()
{
    if((_mags==nullptr)||(_active<0))
        return;

    (*_mags)[_active].clear();

    for(int r=0;r<table->rowCount();++r)
    {
        uchar adr = 0x00;
        uchar in = 0x00;
        uchar x = 0x00;
        QByteArray dat;
        QTableWidgetItem* it;

        it = table->item(r, 0);
        if(it!=nullptr)
            adr = it->text().left(2).toUInt(nullptr, 16)&0x3F;

        it = table->item(r, 1);
        if(it!=nullptr)
            in = it->text().left(2).toUInt(nullptr, 16)&0x03;

        it = table->item(r, 2);
        if(it!=nullptr)
            x = it->text().left(2).toUInt(nullptr, 16)&0x03;

        it = table->item(r, 3);
        if(it!=nullptr)
        {
            QString txt = it->text();
            txt.remove(' ');
            bool ok;
            int val;
            while(!txt.isEmpty())
            {
                val = txt.left(2).toInt(&ok, 16);
                if(ok)
                    dat.push_back((char)val);
                txt = txt.mid(2);
            }
        }

        (*_mags)[_active].append(Message(adr, in, dat, x));
    }

    table->resizeColumnsToContents();
    table->resizeRowsToContents();
}

void MsgPacket::RemoveMsg()
{
    table->removeRow(table->currentRow());
    TableChanged();
}
