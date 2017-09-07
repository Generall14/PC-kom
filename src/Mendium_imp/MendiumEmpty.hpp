#ifndef MENDIUMEMPTY_HPP
#define MENDIUMEMPTY_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumEmpty : public Mendium
{
    Q_OBJECT
public:
    MendiumEmpty();
    virtual ~MendiumEmpty(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame>);
    virtual void Flush();

protected:
    virtual void Run();
};

#endif
