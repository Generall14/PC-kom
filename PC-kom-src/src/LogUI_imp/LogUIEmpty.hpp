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
    virtual void LogString(QString str, bool dirin);

protected:
    QLabel* inLabel = nullptr;
    QLabel* outLabel = nullptr;
};

#endif
