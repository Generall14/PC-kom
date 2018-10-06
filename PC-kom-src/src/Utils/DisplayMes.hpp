#ifndef DISPLAYMES_HPP
#define DISPLAYMES_HPP

#include <QObject>
#include <QFrame>
#include <QLayout>
#include <QLabel>

class DisplayMes : public QObject
{
    Q_OBJECT
public:
    DisplayMes(QFrame* parent);

    void feed(double val, uint cnt, double low, double high, QString unit);
private:
    QFrame* cParent = nullptr;
    QVBoxLayout* mainLay = nullptr;

    QLabel* _nr = nullptr;
    QLabel* _val = nullptr;
    QLabel* _min = nullptr;
    QLabel* _max = nullptr;

    void init();
};

#endif
