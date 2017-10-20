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

protected slots:
    void makeStupidMessage();
    void makeStupidError();

    void ZR3UIFrameAdrChanged(uchar adr);

    void AdrAdd();
    void AdrDelete();
    void AdrOpen();
    void AdrOpenAll();
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

    void AddZR3Dev(QString str);

signals:
    void InternalFrame(QSharedPointer<Frame> frame);
};

#endif
