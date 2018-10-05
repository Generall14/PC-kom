#ifndef DISPLAYMES_HPP
#define DISPLAYMES_HPP

#include <QObject>
#include <QFrame>

class DisplayMes : public QObject
{
    Q_OBJECT
public:
    DisplayMes(QFrame* parent);

    void feed(QString val, uint cnt, QString low, QString high);
private:
    QFrame* cParent = nullptr;

    void init();
};

#endif
