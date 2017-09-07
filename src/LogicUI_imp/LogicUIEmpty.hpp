#ifndef LOGICUIEMPTY_HPP
#define LOGICUIEMPTY_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>

class LogicUIEmpty : public LogicUI
{
    Q_OBJECT
public:
    LogicUIEmpty(QFrame* parent);

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
