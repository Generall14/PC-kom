#include "ParamUi.hpp"
#include <QLayout>
#include <QDebug>
#include <QInputDialog>

const QMap<QString, int> ParamUi::typeSizes{{"bool", 1}, {"char", 1}, {"int16", 2}, {"int32", 4}, {"int48", 6}, {"float24", 3}, {"float32", 4}};

ParamUi::ParamUi(QWidget* parent, param npar):
    _parent(parent),
    _par(npar)
{
    mbox = new QGroupBox(npar.tooltip);
    mbox->setToolTip(npar.desc);
    _parent->layout()->addWidget(mbox);

    QHBoxLayout* mainLay = new QHBoxLayout(mbox);
    mainLay->setMargin(6);

    mVal = new QLabel("--");
    mainLay->addWidget(mVal);
    mVal->setAlignment(Qt::AlignRight);

    QLabel* tl = new QLabel(npar.unit);
    tl->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
    mainLay->addWidget(tl);
}

ParamUi::~ParamUi()
{
    delete mbox;
}

void ParamUi::setData(QByteArray dat)
{
    if(_par.type=="bool")
    {
        if(dat.size()<1)
            return;
        if((uchar)dat.at(0))
            mVal->setText("TRUE");
        else
            mVal->setText("FALSE");
    }
    else if(_par.type=="char")
    {
        if(dat.size()<1)
            return;
//        mVal->setText(QString("0x%1").arg((uchar)dat.at(0)&0xFF, 2, 16, QChar('0')));
        mVal->setText(QString::number((int)(dat.at(0)&0xFF)));
    }
    else if(_par.type=="int16")
    {
        if(dat.size()<2)
            return;
        int temp = 0;
        temp |= (dat.at(0)<<8)&0xFF00;
        temp |= (dat.at(1)<<0)&0x0000;
        mVal->setText(QString::number(temp));
    }
    else if(_par.type=="int32")
    {
        if(dat.size()<4)
            return;
        int temp = 0;
        temp |= (dat.at(0)<<24)&0xFF000000;
        temp |= (dat.at(1)<<16)&0x00FF0000;
        temp |= (dat.at(2)<<8)&0x0000FF00;
        temp |= (dat.at(3)<<0)&0x000000FF;
        mVal->setText(QString::number(temp));
    }
    else if(_par.type=="int48")
    {
        if(dat.size()<6)
            return;
        qint64 temp = 0;
        temp |= (dat.at(0)<<40)&0xFF0000000000;
        temp |= (dat.at(1)<<32)&0x00FF00000000;
        temp |= (dat.at(2)<<24)&0x0000FF000000;
        temp |= (dat.at(3)<<16)&0x000000FF0000;
        temp |= (dat.at(4)<<8)&0x00000000FF00;
        temp |= (dat.at(5)<<0)&0x0000000000FF;
        mVal->setText(QString::number(temp));
    }
}

QByteArray ParamUi::getParamValue(param parr)
{
    QByteArray temp;
    if(parr.type=="bool")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, 0, 1, 1, &ok);
        if(!ok)
            return temp;
        temp.append(i&0xFF);
    }
    else if(parr.type=="char")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, -128, 127, 1, &ok);
        if(!ok)
            return temp;
        temp.append(i&0xFF);
    }
    else if(parr.type=="int16")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, -(2^16)/2, (2^16)/2-1, 1, &ok);
        if(!ok)
            return temp;
        temp.append((i&0xFF00)>>8);
        temp.append((i&0x00FF)>>0);
    }
    else if(parr.type=="int32")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, -(2^32)/2, (2^32)/2-1, 1, &ok);
        if(!ok)
            return temp;
        temp.append((i&0xFF000000)>>24);
        temp.append((i&0x00FF0000)>>16);
        temp.append((i&0x0000FF00)>>8);
        temp.append((i&0x000000FF)>>0);
    }
    else if(parr.type=="int48")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, -(2^32)/2, (2^32)/2-1, 1, &ok);
        if(!ok)
            return temp;
        temp.append((i&0xFF0000000000)>>40);
        temp.append((i&0x00FF00000000)>>32);
        temp.append((i&0x0000FF000000)>>24);
        temp.append((i&0x000000FF0000)>>16);
        temp.append((i&0x00000000FF00)>>8);
        temp.append((i&0x0000000000FF)>>0);
    }
    return temp;
}
