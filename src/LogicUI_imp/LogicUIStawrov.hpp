#ifndef LOGICUISTAWROV_HPP
#define LOGICUISTAWROV_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QGroupBox>
#include <QLayout>
#include <QLineEdit>

class LogicUIStawrov : public LogicUI
{
    Q_OBJECT
public:
    LogicUIStawrov(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

private slots:
    void makeStupidMessage();
    void makeStupidError();

protected:
    void InitTests();

    QVBoxLayout* mainLay = NULL;

    QPushButton* btn = NULL;
    QPushButton* btnE = NULL;

    QLineEdit* leAdr = NULL;
    QLineEdit* leHeader = NULL;
    QLineEdit* leData = NULL;
};

#endif
