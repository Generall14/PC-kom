#include "DisplayMes.hpp"
#include <QLayout>

DisplayMes::DisplayMes(QFrame* parent):
    cParent(parent)
{
    init();
}

void DisplayMes::feed(QString val, uint cnt, QString low, QString high)
{

}

void DisplayMes::init()
{
    mainLay = new QVBoxLayout(cParent);
    mainLay->setMargin(2);
}
