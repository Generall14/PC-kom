#ifndef LOGICUIZR3_HPP
#define LOGICUIZR3_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>

class LogicUIZR3 : public LogicUI
{
    Q_OBJECT
public:
    LogicUIZR3(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

private slots:
    void makeStupidMessage();
    void makeStupidError();

protected:
    QPushButton* btn = NULL;
    QPushButton* btnE = NULL;
};

#endif
