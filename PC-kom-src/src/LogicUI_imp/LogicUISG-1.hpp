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
#include <QTabWidget>
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
    void ReadAll();
    void WriteAll();
    void InternalWriteFrame(QByteArray frame);
    void ReadFlash();
    void WriteFlash();
    void ParseData();

    void StartCollectingData();
    void StoppedCollectingData();
    void UpdateCollectingData(float mval, int madc, int prog);

protected:
    void InitDebug();
    void InitCal();

    int errorCounter = 0;

    QFrame* dbgFrame = nullptr;
    QFrame* calFrame = nullptr;

    //debug:
    QLabel* lblHello = nullptr;
    QLabel* lblCounts = nullptr;
    QLabel* lblTemp = nullptr;
    QLabel* lblZatk = nullptr;
    QLabel* lblLevels = nullptr;
    QLabel* lblVSiPM = nullptr;
    QLabel* lblVbr = nullptr;
    QLabel* lblVBat = nullptr;

    QCheckBox* chkCounts = nullptr;
    QCheckBox* chkTemp = nullptr;
    QCheckBox* chkZatk = nullptr;
    QCheckBox* chkLevels = nullptr;
    QCheckBox* chkVSiPM = nullptr;
    QCheckBox* chkACal = nullptr;

    QVector<QSpinBox*> calV;
    QSpinBox* baseV = nullptr;
    QSpinBox* tempOffset = nullptr;

    QLabel* errorLabel = nullptr;
    QPalette errorPalette;
    QPalette standardPalette;

    QSpinBox* chkDAC = nullptr;

    QSpinBox* readOffset = nullptr;
    QSpinBox* writeOffset = nullptr;
    QSpinBox* writeData = nullptr;

    //kalibracja:
    QSpinBox* chkProbki = nullptr;
    QRadioButton* rbtImp = nullptr;
    QRadioButton* rbtRap = nullptr;
    QCheckBox* chkContin = nullptr;
    QPushButton* btnStop = nullptr;
    QPushButton* btnStart = nullptr;

    QLabel* mPomiar = nullptr;
    QLabel* sPomiar = nullptr;
    QLabel* oPomiar = nullptr;
    QLabel* pPomiar = nullptr;
    QProgressBar* progressBar = nullptr;

    QListWidget* lstKal = nullptr;

    QVector<QSpinBox*> calDst;
    QComboBox* cmbMetoda = nullptr;

    QByteArray data;

signals:
    void InternalFrameReaded(QByteArray);
    void InternalHalt();
};

#endif
