#ifndef VALIDATEDUMBFLOAT_HPP
#define VALIDATEDUMBFLOAT_HPP

#include <QObject>
#include <QValidator>
#include <QString>

class ValidateDumbFloat : public QValidator
{
    Q_OBJECT
public:
    ValidateDumbFloat(QObject* parent = NULL);

    virtual State validate(QString &input, int&) const;

private:
    static const QString znakiFLOAT;
};

#endif
