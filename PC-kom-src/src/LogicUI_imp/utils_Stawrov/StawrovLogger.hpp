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
    STawrovLogger(QObject* parent = nullptr);
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

    bool meaning = false;
    QList<int> total;
    int counts;
    void addToMean(QList<int>& newvals);
    QString meanString();

    QList<QList<int>> shortData;
    QList<QList<int>> longData;
    QList<QList<int>> occData;
    QList<QList<int>> trash;
    QList<int> acc;
    QList<int> mean;
    bool push = false;
    void toFile();

    void OccOn();
    void OccOff();
    void OccReset();
    void skip();

public slots:
    void FrameReaded(QSharedPointer<Frame> frame);

    void startMeaning();
    void stopMeaning();
    void displayMean();

signals:
    void Error(QString msg);
    void StateChanged(QString msg);
    void SetChannels(int channels);
    void File(QString file);
};

#endif
