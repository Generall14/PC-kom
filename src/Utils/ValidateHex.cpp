#include "ValidateHex.hpp"
#include <QDebug>

const QString HexValidator::znakiHEX = "0123456789ABCDEF ";

/**
 * @param rozmiarSlowa - rozmiar słowa w bajtach
 * @param liczbaSlow - maksymalna liczba słów (0 jeżeli nie ma ograniczenia)
 */
HexValidator::HexValidator(int rozmiarSlowa, int liczbaSlow, QObject* parent):
    QValidator(parent),
    _slowo(rozmiarSlowa),
    _liczba(liczbaSlow)
{
}

/**
 * Obrzydliwa funkcja
 */
QValidator::State HexValidator::validate(QString &input, int&) const
{
    int counter = 0;
    QList<int> toRemove;

    input = input.toUpper();
    for(int i=input.length()-1;i>=0;--i)
    {
        if(!znakiHEX.contains(input.at(i)))
            input.remove(i, 1);
    }
    while(input.contains("  "))
        input.replace("  ", " ");

    for(int i=0;i<input.length();i++)
    {
        if(input.at(i)==' ')
            counter = 0;
        else
        {
            counter++;
            if(counter>2*_slowo)
                toRemove.append(i);
        }
    }
    for(int i=toRemove.size()-1;i>=0;--i)
        input.remove(toRemove.at(i), 1);
    if(input.at(0)==' ')
        input.remove(0, 1);

    bool addZeros = false;
    if(input.length()>_slowo*2)
    {
        for(int i=input.length()-1;i>=0;--i)
        {
            if((input.at(i)==' '))
            {
                while((counter<_slowo*2)&&addZeros)
                {
                    input.insert(i+1, '0');
                    counter++;
                }
                counter = 0;
                addZeros = true;
            }
            else
                counter++;

            if(i==0)
            {
                while(counter<_slowo*2)
                {
                    input.insert(i, '0');
                    counter++;
                }
            }
        }
    }
    if(_liczba)
        input = input.left(_liczba*(2*_slowo)+1);
    return QValidator::Acceptable;
}
