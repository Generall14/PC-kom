#ifndef IF11ZR3_HPP
#define IF11ZR3_HPP

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

class IF11ZR3 : public IFPanel, public Restorable
{
    Q_OBJECT
public:
    IF11ZR3(QFrame* parent);
    ~IF11ZR3();

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

protected slots:
    void InitRest();

protected:
    void Init();
    void LoadConfigs();

    QLineEdit* letechACCrnd = nullptr;

    QSpinBox* sbtechRDSECTION = nullptr;

    QSpinBox* sbtechWRSECTION = nullptr;
    QLineEdit* letechWRSECTION = nullptr;

    QLineEdit* letechWrId = nullptr;

    QLabel* labWer = nullptr;
    QLabel* labBuild = nullptr;
    QLabel* labDevId = nullptr;

    QLabel* labStarts = nullptr;
    QLabel* labVDown = nullptr;
    QLabel* labTOn = nullptr;
    QLabel* labTDose = nullptr;
    QLabel* labMDRate = nullptr;
    QLabel* labMUdr = nullptr;
    QLabel* labUdr = nullptr;
};

#endif
