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
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(askDevice()));
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
    {
        for(int i=0;i<_tra.answer.params.size();++i)
        {
            param par = _tra.answer.params.at(i);
            int len = ParamUi::typeSizes.value(par.type, -1);
            if(len<1)
            {
                emit Error("Błądny typ wartości: " + par.type);
                return;
            }
            if(arr.size()<len)
            {
                emit Error("Błądny rozmiar odebranych danych");
                return;
            }
            plist.at(i)->setData(arr.mid(0, len));
            arr.remove(0, len);
        }
    }
}

void TransactionUi::askDevice()
{
    _tra.ask.data.clear();
    for(param pa: _tra.ask.params)
    {
        QByteArray temp = ParamUi::getParamValue(pa);
        if(temp.isEmpty())
            return;
        _tra.ask.data.append(temp);
    }
    emit TransactionRequest(_tra);
}
