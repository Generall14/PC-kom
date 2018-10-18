#ifndef FLAGSDISPLAY_HPP
#define FLAGSDISPLAY_HPP

#include <QObject>
#include <QLayout>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QTimer>

class FlagsDisplay : public QObject
{
    Q_OBJECT
public:
    FlagsDisplay(QLayout* parent, QString name, QStringList flags);
    ~FlagsDisplay();

    void UpdateFlags(QByteArray flags);

public slots:
    void Clear();
    void UpdTimer();

protected:
    void Init();
    void SetFlag(int nr);

    QLayout* cParent=nullptr;
    QString _name;
    QStringList _flags;

    QVector<QLabel*> labs;
    QVBoxLayout *mlay = nullptr;

    QLabel* labTimer = nullptr;
    int intTimer = 0;

    QTimer* timer = nullptr;
    QTimer* timer2 = nullptr;
};

#endif
