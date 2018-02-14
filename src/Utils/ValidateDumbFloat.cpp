#include "ValidateDumbFloat.hpp"
#include <QDebug>

const QString ValidateDumbFloat::znakiFLOAT = "0123456789. ";

ValidateDumbFloat::ValidateDumbFloat(QObject* parent):
    QValidator(parent)
{
}

ValidateDumbFloat::State ValidateDumbFloat::validate(QString &input, int&) const
{
    input.replace(",", ".");

    for(int i=input.length()-1;i>=0;--i)
    {
        if(!znakiFLOAT.contains(input.at(i)))
            input.remove(i, 1);
    }

    while(input.contains("  "))
        input.replace("  ", " ");

    if(input.at(0)==' ')
        input.remove(0, 1);

    return QValidator::Acceptable;
}
