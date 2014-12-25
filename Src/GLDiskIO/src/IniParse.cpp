/*
 * IniParse.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: wim
 */

#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/IniParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

IniParse& IniParse::instance()
{
    static IniParse _gInstance;
    return _gInstance;
}

IniParse::IniParse()
{
}

bool IniParse::loadFile(const std::string& inputFile)
{
    try {
        using namespace boost::property_tree::ini_parser;
        read_ini(inputFile.c_str(), _properties);
    } catch (...) {
        return false;
    }

    return true;
}

void IniParse::saveFile(const char* outputFile)
{
    try {
        using namespace boost::property_tree::ini_parser;
        write_ini(outputFile, _properties);
    } catch (...) {
        std::cerr << "ConfigManager::saveConfigs(): Open file \""
                << outputFile << "\" failed.\n";
    }
}

std::size_t IniParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

const IniParse::Properties& IniParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

IniParse::Properties& IniParse::getChild(const Properties::path_type& path)
{

    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

