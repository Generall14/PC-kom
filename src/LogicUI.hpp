#ifndef LPOGICUI_HPP
#define LPOGICUI_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include "Frame.hpp"

class LogicUI : public QObject
{
    Q_OBJECT
public:
    LogicUI(QFrame* parent);
    virtual ~LogicUI(){}

    virtual void Init() = 0;

public slots:
    virtual void Connected() = 0;
    virtual void Disconnected() = 0;
    virtual void FrameReaded(QSharedPointer<Frame> frame) = 0;

signals:
    void Error(QString msg);
    void WriteFrame(QSharedPointer<Frame> frame);
    void WritePureData(QByteArray data);

protected:
    QFrame* cParent=NULL;
};

#endif
