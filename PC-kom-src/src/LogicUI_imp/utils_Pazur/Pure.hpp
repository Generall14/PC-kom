#ifndef PURE_HPP
#define PURE_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "ConfsPacket.hpp"
#include "MsgPacket.hpp"
#include "../../Utils/Restorable.hpp"
#include <QComboBox>

class Pure : public QObject, public Restorable
{
    Q_OBJECT
public:
    Pure(QFrame* parent);
    ~Pure();

signals:
    void Error(QString msg);
    void Send(QList<Confirm> c, QList<Message> m);

protected slots:
    void InitConfirms();
    void InitMessages();

    void ConfsAddNewSet();
    void ConfsReload();
    void ConfsRemoveSet();
    void ConfsSetChanged();

    void MsgAddNewSet();
    void MsgReload();
    void MsgRemoveSet();
    void MsgSetChanged();

protected:
    void StoreLists();
    void RestoreLists();
    void Init();

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;

    QComboBox* cbcfgs = nullptr;
    QList<QList<Confirm> > _cfs;
    ConfsPacket* _cfsTable = nullptr;

    QComboBox* cbmsgs = nullptr;
    QList<QList<Message> > _msgs;
    MsgPacket* _msgTable = nullptr;
};

#endif
