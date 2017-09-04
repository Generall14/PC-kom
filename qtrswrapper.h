#ifndef QTRSWRAPPER_H
#define QTRSWRAPPER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <iostream>

//#include "serialdevice.hpp"
#include <QSerialPort>
#include <QTimer>
#include <QByteArray>

class QtRSWrapper : public QThread
{
    Q_OBJECT
public:
    explicit QtRSWrapper();

    void run();

signals:
    void Opened();
    void Closed();
    void Readed(QByteArray);
    void FatalReaded(QByteArray);
    void Error(QString);

public slots:
    void Stop();

    void Open(QString portname);
    void Close();

private:
    volatile bool stopRequest=false;

    bool opened=false;

    QSerialPort port;
    QTimer timer;
};

#endif // QTRSWRAPPER_H
