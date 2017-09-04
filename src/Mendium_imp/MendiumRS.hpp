#ifndef MENDIUMRS_HPP
#define MENDIUMRS_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QSerialPort>
#include <QTimer>

class MendiumRS : public Mendium
{
    Q_OBJECT
public:
    MendiumRS();
    virtual ~MendiumRS(){}

public slots:
    virtual void Open(QString desc);
    virtual void Close();

protected:
    virtual void Run();

private:
    QSerialPort port;
    QTimer timer;
};

#endif
