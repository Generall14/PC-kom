#include "Restorable.hpp"
#include <QDebug>

Restorable::Restorable(QString className):
    _className(className)
{
}

void Restorable::Store(QString name, QString value)
{
    Store<>(name, value.toStdString().c_str());
}

void Restorable::Store(QString name, QByteArray value)
{
    QString str;
    for(auto a: value)
        str.append(QString("%1 ").arg(a&0xFF, 2, 16, QChar('0')));
    Store<>(name, str.toStdString().c_str());
}

int Restorable::RestoreAsInt(QString name, int onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_int(onFail);
}

unsigned int Restorable::RestoreAsInt(QString name, unsigned int onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_uint(onFail);
}

float Restorable::RestoreAsFloat(QString name, float onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_float(onFail);
}

bool Restorable::RestoreAsBool(QString name, bool onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return node.attribute(name.toStdString().c_str()).as_bool(onFail);
}

QString Restorable::RestoreAsString(QString name, QString onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
    if(node.empty())
        return onFail;

    return QString(node.attribute(name.toStdString().c_str()).as_string(onFail.toStdString().c_str()));
}

QByteArray Restorable::RestoreAsByteArray(QString name, QByteArray onFail)
{
    pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
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
