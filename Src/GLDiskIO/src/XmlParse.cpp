/**
 * @file XmlParse.cpp
 * @brief xml解析的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <string>
#include <iostream>

#include "GreenLeaf/GLDiskIO/XmlParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief 创建XmlParse的单例对象
 * @return 返回XmlParse的对象
 */
XmlParse& XmlParse::instance()
{
    static XmlParse _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化XmlParse对象
 */
XmlParse::XmlParse()
{
}

/**
 * @brief 载入xml文件
 * @param inputFile xml文件路径
 * @return 返回载入是否成功
 */
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

/**
 * @brief 保存xml文件
 * @param outputFile xml文件路径
 */
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

/**
 * @brief 删除xml节点数据
 * @param key 指定节点
 * @return 返回删除是否成功
 */
std::size_t XmlParse::remove(const Properties::key_type& key)
{
    return _properties.erase(key);
}

/**
 * @brief 获取xml子节点数据
 * @param path 子节点路径
 * @return 返回子节点数据
 */
const XmlParse::Properties& XmlParse::getChild(const Properties::path_type& path) const
{
    return _properties.get_child(path);
}

/**
 * @brief 获取xml子节点数据
 * @param path 子节点路径
 * @return 返回子节点数据
 */
XmlParse::Properties& XmlParse::getChild(const Properties::path_type& path)
{
    return _properties.get_child(path);
}

} } // GreenLeaf::GLDiskIO

