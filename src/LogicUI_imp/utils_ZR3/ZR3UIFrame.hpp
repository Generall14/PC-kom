#ifndef ZR3UIFRAME_HPP
#define ZR3UIFRAME_HPP

#include <QObject>
#include <QFrame>
#include <QPushButton>
#include <QTabWidget>
#include <QStackedWidget>
#include <QListWidget>
#include "../../Frame.hpp"

class ZR3UIFrame : public QObject
{
    Q_OBJECT
public:
    ZR3UIFrame(QFrame* parent, uchar adr);

    void Init();
    uchar Adr() const;

public slots:
    void FrameToUI(QSharedPointer<Frame> frame);

signals:
    void FrameToMendium(QSharedPointer<Frame> frame);
    void Error(QString);

protected:
    QFrame* cFrame = NULL;
    uchar _adr;

    QFrame* dbgFrame = NULL;
    QFrame* suiFrame = NULL;

    QByteArray protHELLO;

    static const char _myAdr = 0xFE;

    void InitDebug();
};

#endif
