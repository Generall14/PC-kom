#ifndef LOGICUITERMINAL_HPP
#define LOGICUITERMINAL_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include "../Utils/Restorable.hpp"
#include "utils_Terminal/Terminal_SendSection.hpp"

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
    virtual void FrameReaded(QSharedPointer<Frame>);

protected slots:
    void SendReceivingParams();
    void SendDisplayParams();

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

    QComboBox* kbRWyswietanie = nullptr;
    QLineEdit* leRHexSign = nullptr;
    QLineEdit* leRInvalid = nullptr;

    const QStringList inputsMethods = {"ASCII", "hex", "mixed"};

    QVector<Terminal_SendSection*> sends;
};

#endif
