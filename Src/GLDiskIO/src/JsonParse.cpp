/**
 * @file JsonParse.cpp
 * @brief Json解析的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/JsonParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief 创建JsonParse的单例对象
 * @return 返回JsonParse对象
 */
JsonParse& JsonParse::instance()
{
    static JsonParse _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化JsonParse对象
 */
JsonParse::JsonParse()
{
}

/**
 * @brief 载入json文件
 * @param inputFile json文件路径
 * @return 返回载入是否成功
 */
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

/**
 * @brief 保存json文件
 * @param outputFile json文件路径
 */
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

/**
 * @brief 删除json节点
 * @param key 指定json节点
 * @return 返回删除是否成功
 */
std::size_t JsonParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

/**
 * @brief 获取json子节点数据
 * @param path 子节点路径
 * @return 返回json子节点
 */
const JsonParse::Properties& JsonParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

/**
 * @brief 获取json子节点数据
 * @param path 子节点路径
 * @return 返回json子节点
 */
JsonParse::Properties& JsonParse::getChild(const Properties::path_type& path)
{
    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

