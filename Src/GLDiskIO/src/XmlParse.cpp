/*
 * XmlParse.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: wim
 */

#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/XmlParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

XmlParse& XmlParse::instance()
{
    static XmlParse _gInstance;
    return _gInstance;
}

XmlParse::XmlParse()
{
}

bool XmlParse::loadFile(const std::string& inputFile)
{
    try {
        using namespace boost::property_tree::xml_parser;
        read_xml(inputFile.c_str(), _properties, no_comments);
    } catch (...) {
        return false;
    }
    return true;
}

void XmlParse::saveFile(const char* outputFile)
{
    try {
        using namespace boost::property_tree::xml_parser;
        write_xml(outputFile, _properties, std::locale(),
                xml_writer_settings<std::string>(' ', 4));
    } catch (...) {
        std::cerr << "ConfigManager::saveConfigs(): Open file \""
                << outputFile << "\" failed.\n";
    }
}

std::size_t XmlParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

const XmlParse::Properties& XmlParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

XmlParse::Properties& XmlParse::getChild(const Properties::path_type& path)
{
    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

