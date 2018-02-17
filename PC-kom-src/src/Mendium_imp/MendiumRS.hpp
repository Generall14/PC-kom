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
    virtual ~MendiumRS();

public slots:
    virtual void Open(QString desc);//"port;prędkość"
    virtual void Close();
    virtual void Write(QSharedPointer<Frame> frame);
    virtual void Flush();

protected slots:
    void readyRead();

protected:
    virtual void Run();

    QSerialPort* port;
};

#endif
