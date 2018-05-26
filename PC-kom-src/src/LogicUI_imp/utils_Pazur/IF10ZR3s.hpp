#ifndef IF10ZR3s_HPP
#define IF10ZR3s_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "../../Utils/Restorable.hpp"
#include "../../Frame.hpp"
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include "src/LogicUI_imp/utils_Pazur/FlagDisplay.hpp"

class IF10ZR3s : public QObject, public Restorable
{
    Q_OBJECT
public:
    IF10ZR3s(QFrame* parent);
    ~IF10ZR3s();

signals:
    void Error(QString msg);
    void Send(QList<Confirm> c, QList<Message> m);

protected slots:
    void InitRest();
    void SendMessage(QByteArray arr, uint ifs = 2);

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

protected:
    void Init();
    void LoadConfigs();

    QString ReadMeasure(QByteArray dat, QString unit);

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;
    QLineEdit* leMagic = nullptr;

    QLabel* labDose = nullptr;
    QDoubleSpinBox* dsbzr3SetDose = nullptr;
    QCheckBox* cbForceDoseAdr = nullptr;
    QCheckBox* cbEnAutoDose = nullptr;
    QLineEdit* leAdrAutoDose = nullptr;
    QSpinBox* sbMsAutoDose = nullptr;

    QLabel* labDoseRate = nullptr;
    QLabel* labDoseRateProbe = nullptr;
    QCheckBox* cbForceDoseRateAdr = nullptr;
    QCheckBox* cbEnAutoDoseRate = nullptr;
    QLineEdit* leAdrAutoDoseRate = nullptr;
    QSpinBox* sbMsAutoDoseRate = nullptr;

    QCheckBox* cbForceWyAlAdr = nullptr;
    QSpinBox* sbMsAutoWyAl = nullptr;
    QCheckBox* cbEnAutoWyAl = nullptr;
    QLineEdit* leAdrAutoWyAl = nullptr;
    QCheckBox* cbEnWyAl = nullptr;
    QSpinBox* sbWyAlTmin = nullptr;
    QComboBox* cmbWyAlMin = nullptr;
    QComboBox* cmbWyAlMax = nullptr;
    QComboBox* cmbWyAlMode = nullptr;
    QComboBox* cmbWyAlSymLvl = nullptr;
    QLabel* labWyAlState = nullptr;
    QCheckBox* cbEnKontrWyAl = nullptr;

    QCheckBox* cbObsEn = nullptr;
    QCheckBox* cbObsInEn = nullptr;
    QCheckBox* cbObsInsEn = nullptr;
    QSpinBox* sbObsIns = nullptr;
    QCheckBox* cbObsOdpEn = nullptr;
    QSpinBox* sbObsOdp = nullptr;
    QCheckBox* cbObsAdrEn = nullptr;
    QLineEdit* leObsAdr = nullptr;

    QComboBox* cbWyStTryb = nullptr;
    QSpinBox* sbWyStTmin = nullptr;

    QLabel* labAlarmState = nullptr;
    QCheckBox* cbAlarmStateDir = nullptr;
    QCheckBox* cbForceDoseRateAAdr = nullptr;
    QSpinBox* sbMsAutoDoseRateA = nullptr;
    QCheckBox* cbEnAutoDoseRateA = nullptr;
    QLineEdit* leAdrAutoDoseRateA = nullptr;

    QCheckBox* cbAlarmStateSetE1 = nullptr;
    QDoubleSpinBox* cbAlarmStateSetTh1 = nullptr;
    QSpinBox* sbAlarmStateSetPod1 = nullptr;
    QSpinBox* sbAlarmStateSetPrze1 = nullptr;

    QCheckBox* cbAlarmStateSetE2 = nullptr;
    QDoubleSpinBox* cbAlarmStateSetTh2 = nullptr;
    QSpinBox* sbAlarmStateSetPod2 = nullptr;
    QSpinBox* sbAlarmStateSetPrze2 = nullptr;

    QCheckBox* cbAlarmStateSetE3 = nullptr;
    QDoubleSpinBox* cbAlarmStateSetTh3 = nullptr;
    QSpinBox* sbAlarmStateSetPod3 = nullptr;
    QSpinBox* sbAlarmStateSetPrze3 = nullptr;

    QCheckBox* cbForceEstsAdr = nullptr;
    QCheckBox* cbEnAutoEst = nullptr;
    QLineEdit* leAdrAutoEst = nullptr;
    QSpinBox* sbMsAutoEst = nullptr;

    QLabel* labEstimatedEnergy = nullptr;
    QLabel* labEstimatedEnergyProbe = nullptr;

    QLabel* labEstimatedNeutron = nullptr;
    QLabel* labEstimatedNeutronProbe = nullptr;

    QLabel* labEstimatedGammaDoseRate = nullptr;
    QLabel* labEstimatedGammaDoseRateProbe = nullptr;

    FlagsDisplay* fsWarn = nullptr;
    FlagsDisplay* fsFault = nullptr;
    FlagsDisplay* fsSerwice = nullptr;
};

#endif
