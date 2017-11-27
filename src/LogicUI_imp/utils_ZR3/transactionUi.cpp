#include "transactionUi.hpp"
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <qDebug>

TransactionUi::TransactionUi(QWidget* parent, TransactionDesc ntra):
    _parent(parent),
    _tra(ntra)
{
    mbox = new QGroupBox(ntra.answer.tooltip);
    _parent->layout()->addWidget(mbox);

    QVBoxLayout* mainLay = new QVBoxLayout(mbox);
    mainLay->setMargin(1);

    QFrame* hbox = new QFrame();
    hbox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    mainLay->addWidget(hbox);

    QHBoxLayout* hLay = new QHBoxLayout(hbox);
    hLay->setMargin(1);

    for(param p: _tra.answer.params)
        plist.append(new ParamUi(hbox, p));

    QPushButton* btn = new QPushButton("Req");
    connect(btn, &QPushButton::clicked, [=](){emit TransactionRequest(_tra);});
    mainLay->addWidget(btn);
}

TransactionUi::~TransactionUi()
{
    for(ParamUi* p: plist)
        delete p;
    delete mbox;
}

void TransactionUi::Done(uchar _header, QByteArray arr)
{
    if(_header==(uchar)_tra.answer.header)
        qDebug() << "ok";
}
