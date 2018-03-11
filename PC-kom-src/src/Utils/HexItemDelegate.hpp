#ifndef HEXITEMDELEGATE_HPP
#define HEXITEMDELEGATE_HPP

#include <QStyledItemDelegate>

class HexItemDelegate : public QStyledItemDelegate
{

public:
    HexItemDelegate(int rozmiarSlowa = 1, int liczbaSlow = 0, QObject *parent = Q_NULLPTR);
    virtual ~HexItemDelegate();

    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const;

private:
    int rozmiar, liczba;
};

#endif
