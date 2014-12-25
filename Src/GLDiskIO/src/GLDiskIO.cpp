/*
 * GLDiskIO.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: wim
 */

#include <iostream>

#include "GreenLeaf/GLDiskIO.h"

namespace GreenLeaf {
namespace GLDiskIO {

DiskIO& DiskIO::instance()
{
    static DiskIO _gInstance;
    return _gInstance;
}

DiskIO::DiskIO()
{
}

const bool DiskIO::loadIniFile(const std::string& inputFile)
{
    return IniParse::instance().loadFile(inputFile);
}

void DiskIO::saveIniFile(const char* outputFile)
{
    IniParse::instance().saveFile(outputFile);
}

const bool DiskIO::loadXmlFile(const std::string& inputFile)
{
    return XmlParse::instance().loadFile(inputFile);
}

void DiskIO::saveXmlFile(const char* outputFile)
{
    XmlParse::instance().saveFile(outputFile);
}

const bool DiskIO::loadJsonFile(const std::string& inputFile)
{
    return JsonParse::instance().loadFile(inputFile);
}

void DiskIO::saveJsonFile(const char* outputFile)
{
    JsonParse::instance().saveFile(outputFile);
}

} } // GreenLeaf::GLDiskIO

