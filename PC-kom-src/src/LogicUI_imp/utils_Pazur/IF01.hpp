#ifndef IF01_HPP
#define IF01_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "../../Utils/Restorable.hpp"
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "IF_panel.hpp"

class IF01 : public IFPanel, public Restorable
{
    Q_OBJECT
public:
    IF01(QFrame* parent);
    ~IF01();

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

protected slots:
    void InitRest();

protected:
    void Init();
    void LoadConfigs();

    QSpinBox* sbwiRDCONST = nullptr;

    QSpinBox* sbwiRDSECTION = nullptr;
    QCheckBox* cbwiRDSECTION = nullptr;
    QLineEdit* lewiRDSECTION = nullptr;

    QSpinBox* sbwiWRSECTION = nullptr;
    QCheckBox* cbwiWRSECTION = nullptr;
    QLineEdit* lewiWRSECTION = nullptr;

    QLineEdit* lewiWRSECTIONnr2 = nullptr;
    QLineEdit* lewiWRSECTION2 = nullptr;

    QLineEdit* lewiGFDA = nullptr;
    QCheckBox* cbwiGFDA = nullptr;
};

#endif
