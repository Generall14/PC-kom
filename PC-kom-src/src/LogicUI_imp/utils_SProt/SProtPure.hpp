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
#include "../../Utils/Restorable.hpp"

class SProtPure : public LogicUI, public Restorable
{
    Q_OBJECT
public:
    SProtPure(QFrame* parent);
    ~SProtPure();

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

    void restore();

signals:

};

#endif
