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

    void UpdThrPWM(int v);
    void UpdBiasPWM(int v);
    void UpdThrPWM(double v);
    void UpdBiasPWM(double v);

protected:
    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;
    QLineEdit* leMagic = nullptr;

    uint _adr;

    QLabel* labWer = nullptr;
    QLabel* labBuild = nullptr;
    QLabel* labStarts = nullptr;
    QLabel* labErrorFLags = nullptr;
    QLabel* labRCLK = nullptr;

    QDoubleSpinBox* sbRegThr = nullptr;
    QSpinBox* sbADCThr = nullptr;
    QDoubleSpinBox* sbRegBias = nullptr;
    QSpinBox* sbADCBias = nullptr;

    const uint MIN_PB_W = 150;

    const double regInt2Float = 1.4*1.0/1024.0;
    const double regFloat2Int = 1/1.4*1023;
};

#endif
