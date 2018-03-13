#include "GlobalXmlFile.hpp"
#include <QDebug>

GlobalXmlFile::GlobalXmlFile()
{
    file.load_file("configs/GlobalConfigFile.xml");
    pugi::xml_node r = file.child("GlobalXmlFile");
    if(r.empty())
        file.append_child("GlobalXmlFile");
    qDebug() << "Konstruktor";
}

GlobalXmlFile::~GlobalXmlFile()
{
    file.save_file("configs/GlobalConfigFile.xml");
    qDebug() << "Destruktor";
}

pugi::xml_node GlobalXmlFile::getMainNode()
{
    static GlobalXmlFile instance;
    return instance.file.child("GlobalXmlFile");
}
