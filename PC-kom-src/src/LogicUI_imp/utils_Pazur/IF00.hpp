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

class IF00 : public QObject, public Restorable
{
    Q_OBJECT
public:
    IF00(QFrame* parent);
    ~IF00();

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

    QLineEdit* leConnO = nullptr;
};

#endif