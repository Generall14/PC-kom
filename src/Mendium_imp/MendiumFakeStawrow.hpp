#ifndef MENDIUMEFAKESTAWROW_HPP
#define MENDIUMEFAKESTAWROW_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumFakeStawrow : public Mendium
{
    Q_OBJECT
public:
    MendiumFakeStawrow();
    virtual ~MendiumFakeStawrow(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame>);
    virtual void Flush();

protected:
    virtual void Run();
    QByteArray sdata;
};

#endif
