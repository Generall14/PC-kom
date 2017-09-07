#ifndef LOGUI_HPP
#define LOGUI_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame.hpp"

class LogUI : public QObject
{
    Q_OBJECT
public:
    LogUI(QFrame* parent);
    virtual ~LogUI(){}

    virtual void Init() = 0;

public slots:
    virtual void FrameWrite(QSharedPointer<Frame> frame) = 0;
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;

signals:
    void Error(QString msg);

protected:
    QFrame* cParent=NULL;
};

#endif
