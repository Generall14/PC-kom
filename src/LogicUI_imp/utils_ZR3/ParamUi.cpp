#include "ParamUi.hpp"
#include <QLayout>
#include <QDebug>
#include <QInputDialog>
#include "../../Utils/StaticUtils.hpp"

const QMap<QString, int> ParamUi::typeSizes{{"bool", 1}, {"char", 1}, {"int16", 2}, {"int32", 4}, {"int48", 6}, {"float24", 3}, {"float32", 4}, {"string", 0}};

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
        mVal->setText(QString::number((int)(dat.at(0)&0xFF)));
    }
    else if(_par.type=="int16")
    {
        mVal->setText(QString::number(SU::byteArray2Int16(dat)));
    }
    else if(_par.type=="int32")
    {
        mVal->setText(QString::number(SU::byteArray2Int32(dat)));
    }
    else if(_par.type=="int48")
    {
        mVal->setText(QString::number(SU::byteArray2Int48(dat)));
    }
    else if(_par.type=="float24")
    {
        mVal->setText(QString::number(SU::float24to32(dat.left(3))));
    }
    else if(_par.type=="float32")
    {
        mVal->setText(QString::number(SU::byteArray2Float32(dat.left(4))));
    }
    else if(_par.type=="string")
    {
        int zero = -1;
        for(int i=0;i<dat.size();++i)
        {
            if((uchar)dat.at(i)==(uchar)0x00)
            {
                zero = i;
                break;
            }
        }
        if(zero<0)
            return;
        mVal->setText(QString(dat.left(zero)));
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
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, -1, -0x7F, 0x7F, 1, &ok);
        if(!ok)
            return temp;
        temp.append(SU::int16ToByteArray(i));
    }
    else if(parr.type=="int32")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, -1, -0x7FFF, 0x7FFF, 1, &ok);
        if(!ok)
            return temp;
        temp.append(SU::int32ToByteArray(i));
    }
    else if(parr.type=="int48")
    {
        bool ok;
        int i = QInputDialog::getInt(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, -1, -0x7FFFFF, 0x7FFFFF, 1, &ok);
        if(!ok)
            return temp;
        temp.append(SU::int48ToByteArray(i));
    }
    else if(parr.type=="float24")
    {
        bool ok;
        float f = QInputDialog::getDouble(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, -1, -2147483647, 2147483647, 9, &ok);
        if(!ok)
            return temp;
        temp.append(SU::float32to24(f));
    }
    else if(parr.type=="float32")
    {
        bool ok;
        float f = QInputDialog::getDouble(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, -1, -2147483647, 2147483647, 9, &ok);
        if(!ok)
            return temp;
        temp.append(SU::float32toByteArray(f));
    }
    else if(parr.type=="string")
    {
//        bool ok;
//        float f = QInputDialog::getDouble(NULL, parr.tooltip+" <"+parr.type+">",parr.desc, 0, -2147483647, 2147483647, 9, &ok);
//        if(!ok)
//            return temp;
//        temp.append(SU::float32toByteArray(f));
    }
    return temp;
}
