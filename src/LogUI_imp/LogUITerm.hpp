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
    virtual void LogString(QString str, bool);

protected:
    QTextEdit* tedit = NULL;
    QPushButton* btnclr = NULL;
    QPushButton* btnsve = NULL;
    QCheckBox* chb = NULL;

    int lineCounter = 0;

    void AppendLog(QString str);

    static const int LINES_CUT_TR = 400;
    static const int LINES_CUT_SAVE_LINES = 100;

protected slots:
    void Clear();
    void WrapSelect(bool sel);
};

#endif
