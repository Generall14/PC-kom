#include "HexItemDelegate.hpp"
#include <QLineEdit>
#include "ValidateHex.hpp"

HexItemDelegate::HexItemDelegate(int rozmiarSlowa, int liczbaSlow, QObject *parent):
    QStyledItemDelegate(parent),
    rozmiar(rozmiarSlowa),
    liczba(liczbaSlow)
{

}

HexItemDelegate::~HexItemDelegate()
{

}

QWidget* HexItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QLineEdit* edit = new QLineEdit(parent);
    edit->setValidator(new HexValidator(rozmiar, liczba));
    return edit;
}
