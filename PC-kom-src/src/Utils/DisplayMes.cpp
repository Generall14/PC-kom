#include "DisplayMes.hpp"
#include <QLayout>
#include <QLabel>
#include <QToolButton>
#include "StaticUtils.hpp"

DisplayMes::DisplayMes(QFrame* parent):
    cParent(parent)
{
    init();
}

void DisplayMes::feed(double val, uint cnt, double low, double high, QString unit)
{
    _nr->setText(QString::number(cnt));
    _val->setText(SU::displayFloat(val, 2, 'f')+unit);
    _min->setText(SU::displayFloat(low, 2, 'f')+unit);
    _max->setText(SU::displayFloat(high, 2, 'f')+unit);
}

void DisplayMes::init()
{
    QPalette tempp = cParent->palette();
    tempp.setColor(QPalette::WindowText, QColor(240, 180, 0));
    tempp.setColor(QPalette::Window, QColor(0, 120, 0));
    cParent->setAutoFillBackground(true);
    cParent->setPalette(tempp);

    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);

    QHBoxLayout* nrLay = new QHBoxLayout();
    mainLay->addLayout(nrLay);
    QLabel* lab = new QLabel("Nr: ");
    nrLay->addWidget(lab);
    _nr = new QLabel("-");
    QFont temp0 = _nr->font();
    temp0.setPointSize(temp0.pointSize()*2);
    temp0.setBold(true);
    _nr->setFont(temp0);
    nrLay->addWidget(_nr);
    nrLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    QToolButton* qtb = new QToolButton();
    nrLay->addWidget(qtb);

    QHBoxLayout* valLay = new QHBoxLayout();
    mainLay->addLayout(valLay);
    valLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    _val = new QLabel("-");
    QFont temp = _val->font();
    temp.setPointSize(temp.pointSize()*4);
    temp.setBold(true);
    _val->setFont(temp);
    valLay->addWidget(_val);
    valLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));

    QHBoxLayout* grLay = new QHBoxLayout();
    mainLay->addLayout(grLay);
    _min = new QLabel("-");
    _min->setFont(temp0);
    grLay->addWidget(_min);
    grLay->addSpacerItem(new QSpacerItem(2, 2, QSizePolicy::Expanding));
    _max = new QLabel("-");
    _max->setFont(temp0);
    grLay->addWidget(_max);
}
