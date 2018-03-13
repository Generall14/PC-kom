#include "GlobalXmlFile.hpp"
#include <QDebug>

GlobalXmlFile::GlobalXmlFile()
{
    file.load_file("configs/GlobalConfigFile.xml");
    qDebug() << "Konstruktor";
}

GlobalXmlFile::~GlobalXmlFile()
{
    file.save_file("configs/GlobalConfigFile.xml");
    qDebug() << "Destruktor";
}

GlobalXmlFile& GlobalXmlFile::get()
{
    static GlobalXmlFile instance;
    return instance;
}

pugi::xml_document *GlobalXmlFile::root()
{
    return &file;
}
