#ifndef STAWROWLOGGER_HPP
#define STAWROWLOGGER_HPP

#include <QFrame>
#include <QString>
#include <QObject>
#include <QSharedPointer>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include "../../Frame.hpp"

class STawrovLogger : public QObject
{
    Q_OBJECT
public:
    STawrovLogger(QObject* parent = NULL);
    ~STawrovLogger();
    void Reset(QString fileName);

private:
    enum state
    {
        state_reseted,
        state_collecting_background,
        state_collecting_meat
    };
    state _state = state_reseted;
    QFile logFile;
    QTextStream logStream;
    int curretChannels = 0;
    int writen = 0;

    void DoSomeStuff(QList<int> channels, bool zajety);
    void AppendLine(QList<int> v);

    QString low, high;

public slots:
    void FrameReaded(QSharedPointer<Frame> frame);

signals:
    void Error(QString msg);
    void StateChanged(QString msg);
    void SetChannels(int channels);
    void File(QString file);
};

#endif
