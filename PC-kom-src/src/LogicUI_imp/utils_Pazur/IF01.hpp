#ifndef IF01_HPP
#define IF01_HPP

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

class IF01 : public QObject, public Restorable
{
    Q_OBJECT
public:
    IF01(QFrame* parent);
    ~IF01();

signals:
    void Error(QString msg);
    void Send(QList<Confirm> c, QList<Message> m);

protected slots:
    void InitRest();
    void SendMessage(QByteArray arr);

protected:
    void Init();
    void LoadConfigs();

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;

    QSpinBox* sbwiRDCONST = nullptr;

    QSpinBox* sbwiRDSECTION = nullptr;
    QCheckBox* cbwiRDSECTION = nullptr;
};

#endif
