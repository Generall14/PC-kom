#ifndef LOGICUISG1_HPP
#define LOGICUISG1_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>

class LogicUISG1 : public LogicUI
{
    Q_OBJECT
public:
    LogicUISG1(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

private slots:

protected:
    void InitDebug();

    QFrame* dbgFrame = NULL;
    QFrame* calFrame = NULL;

    QPushButton* btnHello = NULL;
    QPushButton* btnCounts = NULL;
    QPushButton* btnTemp = NULL;
    QPushButton* btnZatk = NULL;
    QPushButton* btnLevels = NULL;
    QPushButton* btnVSiPM = NULL;
    QPushButton* btnVBat = NULL;
    QLabel* lblHello = NULL;
    QLabel* lblCounts = NULL;
    QLabel* lblTemp = NULL;
    QLabel* lblZatk = NULL;
    QLabel* lblLevels = NULL;
    QLabel* lblVSiPM = NULL;
    QLabel* lblVBat = NULL;

    QPushButton* btnRst = NULL;
    QPushButton* btnACal = NULL;

    QPushButton* btnARep = NULL;
    QCheckBox* chkCounts = NULL;
    QCheckBox* chkTemp = NULL;
    QCheckBox* chkZatk = NULL;
    QCheckBox* chkLevels = NULL;
    QCheckBox* chkVSiPM = NULL;
    QCheckBox* chkACal = NULL;

    QLabel* k00 = NULL;
    QLabel* k01 = NULL;
    QLabel* k02 = NULL;
    QLabel* k10 = NULL;
    QLabel* k11 = NULL;
    QLabel* k12 = NULL;
    QLabel* k20 = NULL;
    QLabel* k21 = NULL;
    QLabel* k22 = NULL;
    QLabel* k30 = NULL;
    QLabel* k31 = NULL;
    QLabel* k32 = NULL;
    QPushButton* kalread = NULL;
    QPushButton* kalreadall = NULL;
    QPushButton* kalwrite = NULL;
    QSpinBox* sbrnumber = NULL;
    QSpinBox* sbwnumber = NULL;
    QSpinBox* sbwvalue = NULL;
};

#endif
