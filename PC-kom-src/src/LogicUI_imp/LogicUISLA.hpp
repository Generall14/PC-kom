#ifndef LOGICUISLA_HPP
#define LOGICUISLA_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QLayout>
#include <QSpinBox>
#include <QGroupBox>

class LogicUISLA : public LogicUI
{
    Q_OBJECT
public:
    LogicUISLA(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

    void StabOn();
    void StabMid();
    void StabOff();
    void GetStabilizationBias();

protected:
    void BuildGUI();

    int CameraId();

    QVBoxLayout* mainLay = nullptr;
    QSpinBox* sbCameraId = nullptr;
};

#endif
