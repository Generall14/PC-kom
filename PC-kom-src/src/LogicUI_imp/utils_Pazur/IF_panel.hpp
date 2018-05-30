#ifndef IF_PANEL_HPP
#define IF_PANEL_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame_imp/utils_Pazur/Confirm.hpp"
#include "Frame_imp/utils_Pazur/Message.hpp"
#include "Frame_imp/FramePazur.hpp"
#include <QLayout>
#include <QLineEdit>

#include "../../Utils/Restorable.hpp"

class IFPanel :public QObject
{
    Q_OBJECT
public:
    IFPanel(QFrame* parent, QString rname);
    ~IFPanel();

signals:
    void Error(QString msg);
    void Send(QList<Confirm> c, QList<Message> m);

public slots:
    void internalFrameReaded(QSharedPointer<Frame> fr);

protected slots:
    void SendMessage(QByteArray arr, uint ifs);

protected:
    void InitBase();

    QFrame* cParent=nullptr;
    QVBoxLayout* mainLay = nullptr;
    QLineEdit* leToAdr = nullptr;
    QLineEdit* leMagic = nullptr;

    const uint MIN_PB_W = 150;

    Restorable* rst = nullptr;
};

#endif
