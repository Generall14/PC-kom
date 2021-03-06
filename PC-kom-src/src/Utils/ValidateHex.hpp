#ifndef VALIDATEHEX_HPP
#define VALIDATEHEX_HPP

#include <QObject>
#include <QValidator>

class HexValidator : public QValidator
{
    Q_OBJECT
public:
    HexValidator(int rozmiarSlowa = 1, int liczbaSlow = 0, QObject* parent = nullptr);

    virtual State validate(QString &input, int& ii) const;

private:
    int _slowo;
    int _liczba;
    static const QString znakiHEX;
};

#endif
