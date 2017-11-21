#ifndef LOGICUISTAWROV_HPP
#define LOGICUISTAWROV_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QRadioButton>
#include "utils_Stawrov/StawrovLogger.hpp"
#include "../Utils/ValidateHex.hpp"
#include "../Utils/ValidateDumbFloat.hpp"

class LogicUIStawrov : public LogicUI
{
    Q_OBJECT
public:
    LogicUIStawrov(QFrame* parent);
    virtual ~LogicUIStawrov();

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

private slots:
    void makeStupidMessage();
    void makeStupidError();
    void setStatus(QString s);
    void setChannels(int s);

    void checkMode();
    bool CalcChannels();
    void SendConfig();

protected:
    void InitTests();
    void LoadConfigs();

    QVBoxLayout* mainLay = NULL;

    QPushButton* btn = NULL;
    QPushButton* btnE = NULL;

    QLineEdit* leAdr = NULL;
    QLineEdit* leHeader = NULL;
    QLineEdit* leData = NULL;

    STawrovLogger* logg = NULL;

    QLabel* statusLabel = NULL;
    QLabel* channelsLabel = NULL;
    QLineEdit* fileAdr = NULL;

    QLineEdit* leZakA = NULL;
    QLineEdit* leAakB = NULL;
    QRadioButton* metUlamki = NULL;
    QRadioButton* metWartosci = NULL;
    QLineEdit* warUlamki = NULL;
    QLineEdit* warWartosci = NULL;
    QLineEdit* lekAdr = NULL;
    QLineEdit* lekAdrLoc = NULL;
    QPushButton* btnr2 = NULL;
    QList<int> values;

    bool modeFromSizes = true;
};

#endif
