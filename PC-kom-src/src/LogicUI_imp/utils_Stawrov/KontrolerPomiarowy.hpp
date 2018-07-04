#ifndef KONTROLERPOMIAROWY_HPP
#define KONTROLERPOMIAROWY_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include "../../Utils/Restorable.hpp"
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>

class KontrolerPomiarowy : public QObject, public Restorable
{
    Q_OBJECT
public:
    KontrolerPomiarowy(uint nr, QFrame* parent);
    ~KontrolerPomiarowy();

signals:
    void Error(QString msg);
    void Send(QByteArray data);

protected slots:
    void InitRest();

private slots:
    void ograniczHV(QString);
    void makeSET_HIGH_VOLTAGE();
    void makeSET_GAIN_OFFSET_AND_TRIGGER();
    void makeSET_CHANNELS();

protected:
    void Init();
    void LoadConfigs();

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    uchar myAdr;

//    QLineEdit* lekAdrLoc = nullptr;
    QLineEdit* leMaxHV = nullptr;
    QLineEdit* leHV = nullptr;
    QLineEdit* leOFFSET = nullptr;
    QLineEdit* leTRIGGER = nullptr;
    QCheckBox* ograniczenie = nullptr;
    QCheckBox* rozniczkowanie = nullptr;
    QComboBox* kcbox = nullptr;

    QLineEdit* leKANALY = nullptr;

    QStringList gnam;
    QMap<QString, uchar> gval;
//    QLineEdit* leToAdr = nullptr;

//    QLineEdit* leConnO = nullptr;
};

#endif
