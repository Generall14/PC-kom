#ifndef IF00_HPP
#define IF00_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "../../Utils/Restorable.hpp"
#include <QComboBox>
#include <QLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCheckBox>
#include "IF_panel.hpp"

class IF00 : public IFPanel, public Restorable
{
    Q_OBJECT
public:
    IF00(QFrame* parent);
    ~IF00();

protected slots:
    void InitRest();

protected:
    void Init();
    void LoadConfigs();

    QLineEdit* leConnO = nullptr;
};

#endif
