#ifndef LOGICUIZR3_HPP
#define LOGICUIZR3_HPP

#include <QFrame>
#include "../LogicUI.hpp"
#include <QPushButton>
#include <QTabWidget>
#include <QListWidget>
#include <QList>
#include "utils_ZR3/ZR3UIFrame.hpp"

class LogicUIZR3 : public LogicUI
{
    Q_OBJECT
public:
    LogicUIZR3(QFrame* parent);
    virtual ~LogicUIZR3();

    virtual void Init();

public slots:
    virtual void Connected();
    virtual void Disconnected();
    virtual void FrameReaded(QSharedPointer<Frame> frame);

private slots:
    void makeStupidMessage();
    void makeStupidError();

    void AdrAdd();
    void AdrDelete();
    void AdrOpen();
    void AdrFromFile();

protected:
    QPushButton* btn = NULL;
    QPushButton* btnE = NULL;

    QTabWidget* qtw = NULL;
    QFrame* dbgFrame = NULL;
    QListWidget* adrLw = NULL;

    QList<ZR3UIFrame*> devsList;
    QList<QFrame*> tabsList;

    bool connected = false;

signals:
    void InternalFrame(QSharedPointer<Frame> frame);
};

#endif
