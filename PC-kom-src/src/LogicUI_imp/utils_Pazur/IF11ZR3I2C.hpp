#ifndef IF11ZR3I2C_HPP
#define IF11ZR3I2C_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "../../Utils/Restorable.hpp"
#include "../../Frame.hpp"
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include "IF_panel.hpp"

class IF11ZR3I2c : public QObject
{
    Q_OBJECT
public:
    IF11ZR3I2c(QFrame* parent, uint adress);
    ~IF11ZR3I2c();

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

signals:
    void send(QByteArray dat);

protected slots:
    void Init();
    void InitRest();

protected:
    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;
    QLineEdit* leMagic = nullptr;

    uint _adr;

    const uint MIN_PB_W = 150;
//    QLineEdit* letechACCrnd = nullptr;

//    QSpinBox* sbtechRDSECTION = nullptr;

//    QSpinBox* sbtechWRSECTION = nullptr;
//    QLineEdit* letechWRSECTION = nullptr;

//    QLineEdit* letechWrId = nullptr;

//    QLabel* labWer = nullptr;
//    QLabel* labBuild = nullptr;
//    QLabel* labDevId = nullptr;

//    QLabel* labStarts = nullptr;
//    QLabel* labVDown = nullptr;
//    QLabel* labTOn = nullptr;
//    QLabel* labTDose = nullptr;
//    QLabel* labMDRate = nullptr;
//    QLabel* labMUdr = nullptr;
//    QLabel* labUdr = nullptr;

//    QSpinBox* sbtechRLadd = nullptr;
//    QLabel* labRLadd = nullptr;
};

#endif
