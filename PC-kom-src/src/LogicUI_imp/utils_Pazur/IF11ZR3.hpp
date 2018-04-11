#ifndef IF11ZR3_HPP
#define IF11ZR3_HPP

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

class IF11ZR3 : public QObject, public Restorable
{
    Q_OBJECT
public:
    IF11ZR3(QFrame* parent);
    ~IF11ZR3();

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

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;

    QLineEdit* letechREQmagic = nullptr;

    QLineEdit* letechACCmagic = nullptr;
    QLineEdit* letechACCrnd = nullptr;

    QSpinBox* sbtechRDSECTION = nullptr;
};

#endif
