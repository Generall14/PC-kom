#ifndef GLOBALXMLFILE_HPP
#define GLOBALXMLFILE_HPP

#include "pugixml.hpp"

class GlobalXmlFile
{
public:
    ~GlobalXmlFile();
    static GlobalXmlFile& get();

    pugi::xml_document *root();

private:
    GlobalXmlFile();

    pugi::xml_document file;
};

#endif
