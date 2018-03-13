#include "Restorable.hpp"
#include <QDebug>

Restorable::Restorable(QString className):
    _className(className)
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
//    pugi::xml_document* dok = GlobalXmlFile::get().root();
//    pugi::xml_node node = dok->child(_className.toStdString().c_str());
//    if(node.empty())
//        node = dok->append_child(_className.toStdString().c_str());
//    node.remove_attribute(fileName.toStdString().c_str());
//    node.append_attribute(fileName.toStdString().c_str()) = textValue.toStdString().c_str();

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

void Restorable::StoreData(QString name, QString value)
{
    StoreData<>(name, value.toStdString().c_str());
}

void Restorable::StoreData(QString name, QByteArray value)
{
    QString str;
    for(auto a: value)
        str.append(QString("%1 ").arg(a&0xFF, 2, 16, QChar('0')));
    StoreData<>(name, str.toStdString().c_str());
}

int Restorable::RestoreAsInt(QString name, int onFail)
{
    pugi::xml_document* dok = GlobalXmlFile::get().root();
    pugi::xml_node node = dok->child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_int(onFail);
}

float Restorable::RestoreAsFloat(QString name, float onFail)
{
    pugi::xml_document* dok = GlobalXmlFile::get().root();
    pugi::xml_node node = dok->child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_float(onFail);

}

bool Restorable::RestoreAsBool(QString name, bool onFail)
{
    pugi::xml_document* dok = GlobalXmlFile::get().root();
    pugi::xml_node node = dok->child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_bool(onFail);
}

QString Restorable::RestoreAsString(QString name, QString onFail)
{
    pugi::xml_document* dok = GlobalXmlFile::get().root();
    pugi::xml_node node = dok->child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return QString(node.attribute(name.toStdString().c_str()).as_string(onFail.toStdString().c_str()));
}

QByteArray Restorable::RestoreAsByteArray(QString name, QByteArray onFail)
{
    pugi::xml_document* dok = GlobalXmlFile::get().root();
    pugi::xml_node node = dok->child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    QString str = QString(node.attribute(name.toStdString().c_str()).as_string(""));
    if(str.isEmpty())
        return QByteArray();

    QByteArray dat;
    str.remove(' ');
    bool ok;
    int val;
    while(!str.isEmpty())
    {
        val = str.left(2).toInt(&ok, 16);
        if(ok)
            dat.push_back((char)val);
        str = str.mid(2);
    }

    return dat;
}
