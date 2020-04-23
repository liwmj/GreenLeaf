/**
 * @file GLDiskIO.cpp
 * @brief GLDiskIO库接口的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>

#include "GreenLeaf/GLDiskIO.h"

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief 创建DiskIO的单例对象
 * @return 返回DiskIO对象
 */
DiskIO& DiskIO::instance()
{
    static DiskIO _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化DiskIO对象
 */
DiskIO::DiskIO()
{
}

/**
 * @brief 载入ini配置文件
 * @param inputFile ini文件的路径
 * @return 返回是否载入成功
 */
const bool DiskIO::loadIniFile(const std::string& inputFile)
{
    return IniParse::instance().loadFile(inputFile);
}

/**
 * @brief 保持ini配置文件
 * @param outputFile ini文件路径
 */
void DiskIO::saveIniFile(const char* outputFile)
{
    IniParse::instance().saveFile(outputFile);
}

/**
 * @brief 载入xml文件
 * @param inputFile xml文件路径
 * @return 返回是否载入成功
 */
const bool DiskIO::loadXmlFile(const std::string& inputFile)
{
    return XmlParse::instance().loadFile(inputFile);
}

/**
 * @brief 保存xml文件
 * @param outputFile xml文件路径
 */
void DiskIO::saveXmlFile(const char* outputFile)
{
    XmlParse::instance().saveFile(outputFile);
}

/**
 * @brief 载入json文件
 * @param inputFile json文件路径
 * @return 返回是否载入成功
 */
const bool DiskIO::loadJsonFile(const std::string& inputFile)
{
    return JsonParse::instance().loadFile(inputFile);
}

/**
 * @brief 保存json文件
 * @param outputFile json文件路径
 */
void DiskIO::saveJsonFile(const char* outputFile)
{
    JsonParse::instance().saveFile(outputFile);
}

} } // GreenLeaf::GLDiskIO

