#ifndef LOGICUIPAZUR_HPP
#define LOGICUIPAZUR_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QList>
#include <QTableWidget>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "../Utils/Restorable.hpp"
#include "utils_Pazur/ConfsPacket.hpp"
#include "utils_Pazur/MsgPacket.hpp"

class LogicUIPazur : public LogicUI, public Restorable
{
    Q_OBJECT
public:
    LogicUIPazur(QFrame* parent);
    virtual ~LogicUIPazur();

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame>);

protected slots:
    void InitGlobals();
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

    void Send();

protected:
    void LoadConfigs();
    void StoreLists();
    void RestoreLists();
    QVBoxLayout* mainLay = nullptr;

    QLineEdit* leMyAdr = nullptr;
    QLineEdit* leToAdr = nullptr;
    QSpinBox* sbId = nullptr;
    QCheckBox* cbFast = nullptr;
    QCheckBox* cbIncrement = nullptr;

    QComboBox* cbcfgs = nullptr;
    QList<QList<Confirm> > _cfs;
    ConfsPacket* _cfsTable = nullptr;

    QComboBox* cbmsgs = nullptr;
    QList<QList<Message> > _msgs;
    MsgPacket* _msgTable = nullptr;
};

#endif
