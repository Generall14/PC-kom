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
};

#endif
