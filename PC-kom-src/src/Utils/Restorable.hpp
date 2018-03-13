#ifndef RESTORABLE_HPP
#define RESTORABLE_HPP

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include "GlobalXmlFile.hpp"
#include "pugixml.hpp"

class Restorable
{
public:
    Restorable(QString className = "XXX");
protected:
    bool Store(QString fileName, QString textValue); // <TODO> w przyszlosci do usuniecia
    bool Restore(QString fileName, QString& textValue); // <TODO> w przyszlosci do usuniecia


    template<typename T> void StoreData(QString name, T value)
    {
        pugi::xml_node node = GlobalXmlFile::getMainNode().child(_className.toStdString().c_str());
        if(node.empty())
            node = GlobalXmlFile::getMainNode().append_child(_className.toStdString().c_str());
        node.remove_attribute(name.toStdString().c_str());
        node.append_attribute(name.toStdString().c_str()) = value;
    }
    void StoreData(QString name, QString value);
    void StoreData(QString name, QByteArray value);


    int RestoreAsInt(QString name, int onFail);
    unsigned int RestoreAsInt(QString name, unsigned int onFail);
    float RestoreAsFloat(QString name, float onFail);
    bool RestoreAsBool(QString name, bool onFail);
    QString RestoreAsString(QString name, QString onFail);
    QByteArray RestoreAsByteArray(QString name, QByteArray onFail);

private:
    QFile _file; // piach
    QTextStream _textStream; // piach
    QString _className;
};

#endif
