#ifndef CONFSPACKET_HPP
#define CONFSPACKET_HPP

#include <QObject>
#include <QBoxLayout>
#include <QList>
#include <QTableWidget>
#include "Frame_imp/utils_Pazur/Confirm.hpp"

class ConfsPacket : QObject
{
    Q_OBJECT
public:
    ConfsPacket(QBoxLayout* upperLayout);

    void Release();
    void SetActive(QList<QList<Confirm> >* cfs, int active);

private:
    void Init(QBoxLayout *upperLayout);
    QTableWidget* table = nullptr;

    QList<QList<Confirm> >* _cfs;
    int _active = -1;

private slots:
    void TableChanged();
    void AddConf();
};

#endif
