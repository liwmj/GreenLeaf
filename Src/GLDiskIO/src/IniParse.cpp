/**
 * @file IniParse.cpp
 * @brief Ini文件解析的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/IniParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief 创建IniParse的单例对象
 * @return 返回IniParse对象
 */
IniParse& IniParse::instance()
{
    static IniParse _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化IniParse对象
 */
IniParse::IniParse()
{
}

/**
 * @brief 载入ini文件
 * @param inputFile ini文件路径
 * @return 返回载入ini文件是否成功
 */
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

/**
 * @brief 保存ini文件
 * @param outputFile ini文件路径
 */
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

/**
 * @brief 删除指定ini节点数据
 * @param key 指定节点
 * @return 返回删除是否成功
 */
std::size_t IniParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

/**
 * @brief 获取ini子节点数据
 * @param path 节点路径
 * @return 返回获取到的ini数据
 */
const IniParse::Properties& IniParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

/**
 * @brief 获取ini子节点数据
 * @param path 节点路径
 * @return 返回获取到的ini数据
 */
IniParse::Properties& IniParse::getChild(const Properties::path_type& path)
{

    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

