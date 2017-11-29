#include "transactionUi.hpp"
#include <QLayout>
#include <QFrame>
#include <QPushButton>
#include <qDebug>
#include <QInputDialog>

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

//    QHBoxLayout* butLay = new QHBoxLayout();
//    mainLay->addLayout(butLay);

    QPushButton* btn = new QPushButton("Auto raport");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(setAutoReport()));
    if(!_tra.answer.autoReport)
        btn->setEnabled(false);
    hLay->addWidget(btn);

    btn = new QPushButton("Request");
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(askDevice()));
    hLay->addWidget(btn);
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
            int len = -1;
            if(par.type=="string")
            {
                for(int i=0;i<arr.size();++i)
                {
                    if((uchar)arr.at(i)==(uchar)0x00)
                    {
                        len = i+1;
                        break;
                    }
                }
            }
            else
                len = ParamUi::typeSizes.value(par.type, -1);
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

void TransactionUi::setAutoReport()
{
    QByteArray temp;
    temp.append(_tra.answer.header);
    bool ok;
    int i = QInputDialog::getInt(NULL, "Okres","Okres raportów w sekundach", 1, 1, 256, 1, &ok);
    if(!ok)
        return;
    temp.append((i&0xFF00)>>8);
    temp.append((i&0x00FF)>>0);
    method task{0x08, true, false, false, 0, 0x88, "", "", QList<param>(), temp};
    method tans{0x88, false, true, false, 500, 0x08, "", ""};
    TransactionDesc ttra(task, tans);
    emit TransactionRequest(ttra);
}
