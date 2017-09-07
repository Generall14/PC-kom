#ifndef LOGUIEMPTY_HPP
#define LOGUIEMPTY_HPP

#include <QFrame>
#include "../LogUI.hpp"
#include <QLabel>
#include <QSharedPointer>
#include "../Frame.hpp"

class LogUIEmpty : public LogUI
{
    Q_OBJECT
public:
    LogUIEmpty(QFrame* parent);

    virtual void Init();

public slots:
    virtual void FrameWrite(QByteArray ba);
    virtual void FrameReaded(QSharedPointer<Frame> frame);

protected:
    QLabel* inLabel = NULL;
    QLabel* outLabel = NULL;
};

#endif
