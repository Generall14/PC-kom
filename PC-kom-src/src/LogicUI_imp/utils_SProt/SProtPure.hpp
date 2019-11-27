#ifndef SPROTPURE_HPP
#define SPROTPURE_HPP

#include <QFrame>
#include "../../LogicUI.hpp"
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
#include <QLineEdit>

class SProtPure : public LogicUI
{
    Q_OBJECT
public:
    SProtPure(QFrame* parent);

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

protected slots:
    void sendData();

protected:
    QLineEdit* lecmd = nullptr;
    QLineEdit* ledata = nullptr;


signals:

};

#endif
