#ifndef MENDIUMEFAKEZR3_HPP
#define MENDIUMEFAKEZR3_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumFakeZR3 : public Mendium
{
    Q_OBJECT
public:
    MendiumFakeZR3();
    virtual ~MendiumFakeZR3(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame>);
    virtual void Flush();

protected:
    virtual void Run();

    unsigned char myAdr = 0x01;
    unsigned char nextAdr = 0xFF;
};

#endif
