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

    void makeSET_CHANNELS();

    void PackAndSend(QByteArray data);

    void StartMeaning();
    void StopMeaning();
    void TimeoutedMean();

    void RemoveTab();
    void AddTab(QString adr);

protected:
    void InitTests();
    void LoadConfigs();

    QVBoxLayout* mainLay = nullptr;

    QPushButton* btn = nullptr;
    QPushButton* btnE = nullptr;

    QLineEdit* leAdr = nullptr;
    QLineEdit* leData = nullptr;

    STawrovLogger* logg = nullptr;

    QLabel* statusLabel = nullptr;
    QLabel* fileLabel = nullptr;
    QLabel* channelsLabel = nullptr;
    QLineEdit* fileAdr = nullptr;

    QLineEdit* leKANALY = nullptr;

    QLineEdit* lekAdr = nullptr;

    QCheckBox* cbIgnoreFirst = nullptr;

    bool modeFromSizes = true;
    QStringList gnam;
    QMap<QString, uchar> gval;

    QLabel* seconds = nullptr;
    QSpinBox* sbseconds = nullptr;
    QPushButton* btnme = nullptr;
    QPushButton* btnms = nullptr;
    QTimer* meanTimer = nullptr;
    int secondsOfMeaning = 0;

    QTabWidget* tw = nullptr;
    QPushButton* btnremove = nullptr;
    QLineEdit* leNewAdr = nullptr;
};

#endif
