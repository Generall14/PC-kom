#ifndef LOGICUISPROT_HPP
#define LOGICUISPROT_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QTabWidget>
#include <QFrame>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QSharedPointer>
#include <QRadioButton>
#include <QProgressBar>
#include <QListWidget>
#include <QComboBox>
#include <QTabWidget>
#include "../Factory.hpp"

class SProtPure;

class LogicUISProt : public LogicUI
{
    Q_OBJECT
public:
    LogicUISProt(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

protected slots:


protected:
    QTabWidget* tw = nullptr;

    QVector<QSharedPointer<LogicUI> > tabs;

signals:
    void iFrameReaded(QSharedPointer<Frame> frame);
    void iDisconnected();
    void iConnected();
};

#endif
