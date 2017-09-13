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
#include <QSharedPointer>
#include "../Factory.hpp"

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

protected slots:
    QSharedPointer<Frame> MakeFrame(uchar header, int val = 0);
    void SendFrame(uchar header, int val = 0);
    void SendAutoReportConfig();
    void ReadSingleCal();
    void WriteSingleCal();
    void ReadAll();
    void InternalWriteFrame(QByteArray frame);

protected:
    void InitDebug();

    QFrame* dbgFrame = NULL;
    QFrame* calFrame = NULL;

    QLabel* lblHello = NULL;
    QLabel* lblCounts = NULL;
    QLabel* lblTemp = NULL;
    QLabel* lblZatk = NULL;
    QLabel* lblLevels = NULL;
    QLabel* lblVSiPM = NULL;
    QLabel* lblVBat = NULL;

    QCheckBox* chkCounts = NULL;
    QCheckBox* chkTemp = NULL;
    QCheckBox* chkZatk = NULL;
    QCheckBox* chkLevels = NULL;
    QCheckBox* chkVSiPM = NULL;
    QCheckBox* chkACal = NULL;

    QVector<QLabel*> calV;
    QSpinBox* sbrnumber = NULL;
    QSpinBox* sbwnumber = NULL;
    QSpinBox* sbwvalue = NULL;

    QLabel* errorLabel = NULL;
    QPalette errorPalette;
    QPalette standardPalette;

    int errorCounter = 0;

signals:
    void InternalFrameReaded(QByteArray);
};

#endif
