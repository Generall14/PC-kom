#ifndef FLAGSDISPLAY_HPP
#define FLAGSDISPLAY_HPP

#include <QObject>
#include <QLayout>
#include <QString>
#include <QStringList>
#include <QLabel>

class FlagsDisplay : public QObject
{
    Q_OBJECT
public:
    FlagsDisplay(QLayout* parent, QString name, QStringList flags);
    ~FlagsDisplay();

    void Clear();
    void UpdateFlags(QByteArray flags);

protected:
    void Init();
    void SetFlag(int nr);

    QLayout* cParent=nullptr;
    QString _name;
    QStringList _flags;

    QVector<QLabel*> labs;
    QVBoxLayout *mlay = nullptr;
};

#endif
