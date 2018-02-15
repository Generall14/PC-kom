#ifndef TERMINAL_SENDSECTION_HPP
#define TERMINAL_SENDSECTION_HPP

#include <QObject>
#include <QLayout>
#include <QString>
#include <QTimer>
#include <QLineEdit>
#include <QCheckBox>
#include <QSpinBox>
#include <QBoxLayout>

class Terminal_SendSection : public QObject
{
    Q_OBJECT
public:
    Terminal_SendSection(QBoxLayout *upperLayout);
    ~Terminal_SendSection();

    QString Store() const;
    void Restore(QString desc);
    void Enable();
    void Disable();

public slots:
    void Stop();

private slots:
    void timeoutChanged(int val);

signals:
    void Send(QString str);

private:
    QTimer* timer = nullptr;
    bool pause = false;

    QLineEdit* leSend = nullptr;
    QToolButton* tb = nullptr;
    QCheckBox* cb = nullptr;
    QSpinBox* sb = nullptr;
};

#endif
