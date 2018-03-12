#ifndef CONFSPACKET_HPP
#define CONFSPACKET_HPP

#include <QObject>
#include <QBoxLayout>
#include <QList>
#include <QTableWidget>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Utils/pugixml.hpp"

class ConfsPacket : QObject
{
    Q_OBJECT
public:
    ConfsPacket(QBoxLayout* upperLayout);

    void Release();
    void SetActive(QList<QList<Confirm> >* cfs, int active);
    QList<Confirm> getCurrent();

private:
    void Init(QBoxLayout *upperLayout);
    QTableWidget* table = nullptr;
    QPushButton* btnd = nullptr;
    QPushButton* btnu = nullptr;

    QList<QList<Confirm> >* _cfs = nullptr;
    int _active = -1;

private slots:
    void TableChanged();
    void RemoveConf();
};

#endif
