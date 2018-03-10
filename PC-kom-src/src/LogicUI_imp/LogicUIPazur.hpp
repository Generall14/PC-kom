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

    void ConfStoreCurrent();
    void ConfsAddNewSet();
    void ConfsSetChanged();
    void ConfsAddNewConf();

    void Send();

protected:
    void LoadConfigs();
    QVBoxLayout* mainLay = nullptr;

    QLineEdit* leMyAdr = nullptr;
    QSpinBox* sbId = nullptr;
    QCheckBox* cbFast = nullptr;
    QCheckBox* cbIncrement = nullptr;

    QComboBox* cbcfgs = nullptr;
    QTableWidget* twcfgs = nullptr;
    int currentConf=-1;

    QList<QList<Confirm> > _cfs;
    QList<QList<Message> > _msgs;
};

#endif
