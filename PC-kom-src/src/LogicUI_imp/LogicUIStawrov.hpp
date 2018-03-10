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
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include "utils_Stawrov/StawrovLogger.hpp"
#include "../Utils/ValidateHex.hpp"
#include "../Utils/ValidateDumbFloat.hpp"
#include "../Utils/Restorable.hpp"

class LogicUIStawrov : public LogicUI, public Restorable
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
    void setStatus(QString s);
    void setFile(QString s);
    void setChannels(int s);

    void ograniczHV(QString);

    void makeSYNCH_AND_START();
    void makeRESET_SLAVE();
    void makeRESET_MASTER();
    void makeSET_HIGH_VOLTAGE();
    void makeSET_GAIN_OFFSET_AND_TRIGGER();
    void makeSET_CHANNELS();

    void PackAndSend(QByteArray data);

    void StartMeaning();
    void StopMeaning();
    void TimeoutedMean();

protected:
    void InitTests();
    void LoadConfigs();

    QVBoxLayout* mainLay = NULL;

    QPushButton* btn = NULL;
    QPushButton* btnE = NULL;

    QLineEdit* leAdr = NULL;
    QLineEdit* leData = NULL;

    STawrovLogger* logg = NULL;

    QLabel* statusLabel = NULL;
    QLabel* fileLabel = NULL;
    QLabel* channelsLabel = NULL;
    QLineEdit* fileAdr = NULL;

    QLineEdit* leHV = NULL;
    QLineEdit* leMaxHV = NULL;
    QLineEdit* leOFFSET = NULL;
    QLineEdit* leTRIGGER = NULL;
    QLineEdit* leKANALY = nullptr;

    QLineEdit* lekAdr = NULL;
    QLineEdit* lekAdrLoc = NULL;

    QComboBox* kcbox = nullptr;
    QCheckBox* rozniczkowanie = nullptr;
    QCheckBox* ograniczenie = nullptr;

    bool modeFromSizes = true;
    QStringList gnam;
    QMap<QString, uchar> gval;

    QLabel* seconds = nullptr;
    QSpinBox* sbseconds = nullptr;
    QPushButton* btnme = nullptr;
    QPushButton* btnms = nullptr;
    QTimer* meanTimer = nullptr;
    int secondsOfMeaning = 0;
};

#endif