#include "ParamUi.hpp"
#include <QLayout>

ParamUi::ParamUi(QWidget* parent, param npar):
    _parent(parent),
    _par(npar)
{
    mbox = new QGroupBox(npar.tooltip);
    mbox->setToolTip(npar.desc);
    _parent->layout()->addWidget(mbox);

    QHBoxLayout* mainLay = new QHBoxLayout(mbox);
    mainLay->setMargin(6);
}

ParamUi::~ParamUi()
{
    delete mbox;
}
