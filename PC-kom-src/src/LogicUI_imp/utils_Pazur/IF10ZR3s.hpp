#ifndef IF10ZR3s_HPP
#define IF10ZR3s_HPP

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

class IF10ZR3s : public QObject, public Restorable
{
    Q_OBJECT
public:
    IF10ZR3s(QFrame* parent);
    ~IF10ZR3s();

signals:
    void Error(QString msg);
    void Send(QList<Confirm> c, QList<Message> m);

protected slots:
    void InitRest();
    void SendMessage(QByteArray arr);

public slots:
    void internalFrameReaded(QSharedPointer<Frame>);

protected:
    void Init();
    void LoadConfigs();

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;

//    QLineEdit* letechREQmagic = nullptr;

//    QLineEdit* letechACCmagic = nullptr;
//    QLineEdit* letechACCrnd = nullptr;

//    QSpinBox* sbtechRDSECTION = nullptr;

//    QLineEdit* letechWRSECTIONmagic = nullptr;
//    QSpinBox* sbtechWRSECTION = nullptr;
//    QLineEdit* letechWRSECTION = nullptr;
};

#endif
