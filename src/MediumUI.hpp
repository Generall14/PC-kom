#ifndef MEDIUMUI_HPP
#define MEDIUMUI_HPP

#include <QFrame>
#include <QString>
#include <QObject>

class MediumUI : public QObject
{
    Q_OBJECT
public:
    MediumUI(QFrame* parent);
    virtual ~MediumUI(){}

    virtual void Init() = 0;

public slots:
    virtual void Connected() = 0;
    virtual void Disconnected() = 0;

signals:
    void ConnectRequest(QString desc);
    void DisconnectRequest();
    void Error(QString msg);

protected:
    QFrame* cParent=NULL;
};

#endif
