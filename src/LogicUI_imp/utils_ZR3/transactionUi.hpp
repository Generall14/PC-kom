#ifndef TRANSACTIONUI_HPP
#define TRANSACTIONUI_HPP

#include <QObject>
#include <QWidget>
#include <QGroupBox>
#include <QLabel>
#include <QList>

#include "ParamUi.hpp"
#include "transactionDesc.hpp"

class TransactionUi : public QObject
{
    Q_OBJECT
public:
    TransactionUi(QWidget* parent, TransactionDesc ntra);
    ~TransactionUi();
private:
    QWidget* _parent = NULL;
    TransactionDesc _tra;
    QGroupBox* mbox = NULL;
    QList<ParamUi*> plist;

private slots:
    void askDevice();

signals:
    void TransactionRequest(TransactionDesc t);
    void Error(QString);

public slots:
    void Done(uchar _header, QByteArray arr);
};

#endif
