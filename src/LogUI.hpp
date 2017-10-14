#ifndef LOGUI_HPP
#define LOGUI_HPP

#include <QFrame>
#include <QString>
#include <QObject>

class LogUI : public QObject
{
    Q_OBJECT
public:
    LogUI(QFrame* parent);
    virtual ~LogUI(){}

    virtual void Init() = 0;

public slots:
    virtual void LogString(QString str, bool dirin) = 0;

signals:
    void Error(QString msg);

protected:
    QFrame* cParent=NULL;
};

#endif
