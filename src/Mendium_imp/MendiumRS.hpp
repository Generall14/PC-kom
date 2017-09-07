#ifndef MENDIUMRS_HPP
#define MENDIUMRS_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumRS : public Mendium
{
    Q_OBJECT
public:
    MendiumRS();
    virtual ~MendiumRS(){}

public slots:
    virtual void Open(QString desc);
    virtual void Close();
    virtual void Write(QByteArray data);
    virtual void Flush();

protected:
    virtual void Run();

    QSerialPort port;
    QMutex mutex;
    QByteArray writeByffer;
};

#endif
