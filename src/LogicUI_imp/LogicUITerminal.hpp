#ifndef LOGICUITERMINAL_HPP
#define LOGICUITERMINAL_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include "../Utils/Restorable.hpp"
//#include <QPushButton>

class LogicUITerminal : public LogicUI, public Restorable
{
    Q_OBJECT
public:
    LogicUITerminal(QFrame* parent);
    virtual ~LogicUITerminal();

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

protected slots:
    void SendReceivingParams();

    void SendData(QString txt);

protected:
    void InitReceive();
    void InitDisplay();
    void InitSend();
    void LoadConfigs();
    QVBoxLayout* mainLay = nullptr;

    QSpinBox* sbBytes = nullptr;
    QSpinBox* sbTimeout = nullptr;

    QComboBox* kbSWprowadzanie = nullptr;
    QLineEdit* leSHexSign = nullptr;

    QLineEdit* leSend1 = nullptr;

    const QStringList inputsMethods = {"ASCII", "hex", "mixed"};

//    QPushButton* btn = NULL;
//    QPushButton* btnE = NULL;
};

#endif
