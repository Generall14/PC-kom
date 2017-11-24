#include "transactionUi.hpp"
#include <QLayout>

TransactionUi::TransactionUi(QWidget* parent, TransactionDesc ntra):
    _parent(parent),
    _tra(ntra)
{
    mbox = new QGroupBox(ntra.answer.tooltip);
    _parent->layout()->addWidget(mbox);

    QVBoxLayout* mainLay = new QVBoxLayout(mbox);
    mainLay->setMargin(6);

    for(param p: _tra.answer.params)
        plist.append(new ParamUi(mbox, p));
}

TransactionUi::~TransactionUi()
{
    for(ParamUi* p: plist)
        delete p;
    delete mbox;
}
