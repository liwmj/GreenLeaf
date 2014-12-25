/*
 * JsonParse.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: wim
 */

#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/JsonParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

JsonParse& JsonParse::instance()
{
    static JsonParse _gInstance;
    return _gInstance;
}

JsonParse::JsonParse()
{
}

bool JsonParse::loadFile(const std::string& inputFile)
{
    try {
        using namespace boost::property_tree::json_parser;
        read_json(inputFile.c_str(), _properties);
    } catch (...) {
        return false;
    }
    return true;
}

void JsonParse::saveFile(const char* outputFile)
{
    try {
        using namespace boost::property_tree::json_parser;
        write_json(outputFile, _properties);
    } catch (...) {
        std::cerr << "ConfigManager::saveConfigs(): Open file \""
                << outputFile << "\" failed.\n";
    }
}

std::size_t JsonParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

const JsonParse::Properties& JsonParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

JsonParse::Properties& JsonParse::getChild(const Properties::path_type& path)
{
    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

