#ifndef PUREMESSAGE_HPP
#define PUREMESSAGE_HPP

#include <QByteArray>
#include <QString>
#include <QByteArray>

class PureMessage
{
public:
    PureMessage(QByteArray arr); // pelen zakres danych (adres i rozmiar tez)

    QString desc() const;

    static QByteArray wiRDCONST(uint offset); // same dane wlasciwe (bez bajtow adresu i rozmiaru)
private:
    QByteArray _arr;
};

#endif
