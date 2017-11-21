#include "Restorable.hpp"

Restorable::Restorable()
{
    _textStream.setDevice(&_file);
}

/**
 * Zapisuje tekst textValue do pliku (nadpisuje plik)
 * @param fileName - nazwa pliku
 * @param textValue - tekst
 * @return 0 - ok, 1 - błąd
 */
bool Restorable::Store(QString fileName, QString textValue)
{
    _file.setFileName(fileName);
    if(_file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::WriteOnly))
    {
        _textStream << textValue;
        _textStream.flush();
        _file.close();
        return 0;
    }
    return 1;
}

/**
 * Odczytuje tekst z pliku fileName i umieszcza go w textValue
 * @param fileName - nazwa pliku
 * @param textValue - odczytany tekst
 * @return 0 - ok, 1 - błąd
 */
bool Restorable::Restore(QString fileName, QString& textValue)
{
    textValue.clear();
    _file.setFileName(fileName);
    if(_file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        textValue = _textStream.readLine();
        _file.close();
        return 0;
    }
    return 1;
}
