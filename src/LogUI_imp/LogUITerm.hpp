#ifndef LOGUITERM_HPP
#define LOGUITERM_HPP

#include <QFrame>
#include "../LogUI.hpp"
#include <QSharedPointer>
#include "../Frame.hpp"
#include <QTextEdit>
#include <QPushButton>
#include "QCheckBox"

class LogUITerm : public LogUI
{
    Q_OBJECT
public:
    LogUITerm(QFrame* parent);

    virtual void Init();

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame);
    virtual void FrameReaded(QSharedPointer<Frame> frame);

protected:
    QTextEdit* tedit = NULL;
    QPushButton* btnclr = NULL;
    QPushButton* btnsve = NULL;
    QCheckBox* chb = NULL;

protected slots:
    void Clear();
    void WrapSelect(bool sel);
};

#endif
