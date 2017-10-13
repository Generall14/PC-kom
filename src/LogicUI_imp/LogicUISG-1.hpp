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
#include <QRadioButton>
#include <QProgressBar>
#include <QListWidget>
#include <QComboBox>
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

    void StartCollectingData();
    void StoppedCollectingData();
    void UpdateCollectingData(float mval, int madc, int prog);

protected:
    void InitDebug();
    void InitCal();

    int errorCounter = 0;

    QFrame* dbgFrame = NULL;
    QFrame* calFrame = NULL;

    //debug:
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

    QSpinBox* chkDAC = NULL;

    //kalibracja:
    QSpinBox* chkProbki = NULL;
    QRadioButton* rbtImp = NULL;
    QRadioButton* rbtRap = NULL;
    QCheckBox* chkContin = NULL;
    QPushButton* btnStop = NULL;
    QPushButton* btnStart = NULL;

    QLabel* mPomiar = NULL;
    QLabel* sPomiar = NULL;
    QLabel* oPomiar = NULL;
    QLabel* pPomiar = NULL;
    QProgressBar* progressBar = NULL;

    QListWidget* lstKal = NULL;

    QVector<QSpinBox*> calDst;
    QComboBox* cmbMetoda = NULL;

signals:
    void InternalFrameReaded(QByteArray);
    void InternalHalt();
};

#endif
