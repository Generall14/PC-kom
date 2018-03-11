#ifndef MSGPACKET_HPP
#define MSGPACKET_HPP

#include <QObject>
#include <QBoxLayout>
#include <QList>
#include <QTableWidget>
#include <QPushButton>
#include "Frame_imp/utils_Pazur/Message.hpp"

class MsgPacket : QObject
{
    Q_OBJECT
public:
    MsgPacket(QBoxLayout* upperLayout);

    void Release();
    void SetActive(QList<QList<Message> >* msg, int active);
    QList<Message> getCurrent();

private:
    void Init(QBoxLayout *upperLayout);
    QTableWidget* table = nullptr;
    QPushButton* btnd = nullptr;
    QPushButton* btnu = nullptr;

    QList<QList<Message> >* _mags = nullptr;
    int _active = -1;

private slots:
    void TableChanged();
    void RemoveMsg();
};

#endif
