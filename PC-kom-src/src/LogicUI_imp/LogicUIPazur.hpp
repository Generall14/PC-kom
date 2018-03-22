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
#include "utils_Pazur/Pure.hpp"
#include "utils_Pazur/IF01.hpp"

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
    void InitTabs();

    void Send(QList<Confirm> c, QList<Message> m);

protected:
    void LoadConfigs();
    QVBoxLayout* mainLay = nullptr;

    QLineEdit* leMyAdr = nullptr;
    QLineEdit* leToAdr = nullptr;
    QSpinBox* sbId = nullptr;
    QCheckBox* cbFast = nullptr;
    QCheckBox* cbIncrement = nullptr;
    QCheckBox* cbKwitowanie = nullptr;

    QTabWidget* tw = nullptr;
    Pure* _pure = nullptr;
    IF01* _if01 = nullptr;
};

#endif
