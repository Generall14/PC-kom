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
    void SendMessage(QByteArray arr);

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

protected:
    void Init();
    void LoadConfigs();

    QString ReadMeasure(QByteArray dat, QString unit);

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;

    QLabel* labDose = nullptr;
    QDoubleSpinBox* dsbzr3SetDose = nullptr;

    QLabel* labDoseRate = nullptr;
    QLabel* labDoseRateProbe = nullptr;

    QLabel* labEstimatedEnergy = nullptr;
    QLabel* labEstimatedEnergyProbe = nullptr;

    QLabel* labEstimatedNeutron = nullptr;
    QLabel* labEstimatedNeutronProbe = nullptr;

    QLabel* labEstimatedGammaDoseRate = nullptr;
    QLabel* labEstimatedGammaDoseRateProbe = nullptr;

//    QLineEdit* letechACCmagic = nullptr;
//    QLineEdit* letechACCrnd = nullptr;

//    QSpinBox* sbtechRDSECTION = nullptr;

//    QLineEdit* letechWRSECTIONmagic = nullptr;
//    QSpinBox* sbtechWRSECTION = nullptr;
//    QLineEdit* letechWRSECTION = nullptr;
};

#endif
