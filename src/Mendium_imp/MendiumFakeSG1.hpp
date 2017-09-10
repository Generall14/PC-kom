#ifndef MENDIUMFAKSESG1_HPP
#define MENDIUMFAKSESG1_HPP

#include "../Mendium.hpp"
#include <QObject>
#include <QTimer>
#include <QMutexLocker>
#include <QMutex>

class MendiumFakeSG1 : public Mendium
{
    Q_OBJECT
public:
    MendiumFakeSG1();
    virtual ~MendiumFakeSG1(){}

public slots:
    virtual void Open(QString);
    virtual void Close();
    virtual void Write(QSharedPointer<Frame> frame);
    virtual void Flush();

protected:
    virtual void Run();
    void SendFrame(char header, int val);

    int arep = 0x00;
    int rrep = 0x00;
    const int helloresp = 0x008181;

    const int shiftCnt = 0;
    const int shiftACal = 2;
    const int shiftDAC = 3;
    const int shiftTemp = 4;
    const int shiftLevels = 5;
    const int shiftZatk = 6;

    bool helloreq = false;
    bool battreq = false;
};

#endif
