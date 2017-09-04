#ifndef MENDIUM_HPP
#define MENDIUM_HPP

#include <QObject>
#include <QThread>
#include <QByteArray>

class Mendium : public QThread
{
    Q_OBJECT
public:
    Mendium();
    virtual ~Mendium(){}

    void run();

public slots:
    void Stop();
    bool isOpened();
    virtual void Open(QString desc) = 0;
    virtual void Close() = 0;

protected:
    virtual void Run() = 0;

    bool opened = false;

    int readTimeout;
    int writeTimeout;
    int frameLength;

signals:
    void Opened();
    void Closed();
    void Readed(QByteArray);
    void FatalReaded(QByteArray);
    void Error(QString);

private:
    volatile bool stopRequest = false;
};

#endif


//#include <QSerialPort>
//#include <QTimer>
//private:
//    QSerialPort port;
//    QTimer timer;
