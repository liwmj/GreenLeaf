/**
 * @file GLDiskIO.h
 * @brief GLDiskIO库的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef GLDISKIO_H
#define GLDISKIO_H

#if defined(__WIN32__)
    #if defined(GLDISKIO_LIBRARY)
    #  define GLDISKIO_SHARED_EXPORT __declspec(dllexport)
    #else
    #  define GLDISKIO_SHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #define GLDISKIO_SHARED_EXPORT
#endif

#include <string>
#include <boost/noncopyable.hpp>

#include "GreenLeaf/GLDiskIO/IniParse.h"
#include "GreenLeaf/GLDiskIO/XmlParse.h"
#include "GreenLeaf/GLDiskIO/JsonParse.h"

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief DiskIO库的接口类
 */
class GLDISKIO_SHARED_EXPORT DiskIO: private boost::noncopyable
{
public:
    typedef boost::property_tree::ptree Properties;

    static DiskIO& instance();

    /** 载入ini文件 */
    const bool loadIniFile(const std::string& inputFile);

    /** 保存ini文件 */
    void saveIniFile(const char* outputFile);

    /** 获取ini数据 */
    template<typename Type>
    Type iniData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return IniParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    Type iniData(const Properties& node, const Properties::path_type& path,
            const Type& defaultValue = Type()) {
        return IniParse::instance().get(node, path, defaultValue);
    }

    /** 设置ini数据 */
    template<typename Type>
    void setIniData(const Properties::path_type& path, const Type& newValue) {
        return IniParse::instance().set(path, newValue);
    }
    template<typename Type>
    void setIniData(const Properties& node, const Properties::path_type& path,
            const Type& newValue) {
        return IniParse::instance().set(node, path, newValue);
    }

    /** 载入xml文件 */
    const bool loadXmlFile(const std::string& inputFile);

    /**保存xml文件 */
    void saveXmlFile(const char* outputFile);

    /** 获取xml数据 */
    template<typename Type>
    Type xmlData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return XmlParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    Type xmlData(const Properties& node, const Properties::path_type& path,
            const Type& defaultValue = Type()) {
        return XmlParse::instance().get(node, path, defaultValue);
    }

    /** 设置xml数据 */
    template<typename Type>
    void setXmlData(const Properties::path_type& path, const Type& newValue) {
        return XmlParse::instance().set(path, newValue);
    }
    template<typename Type>
    void setXmlData(const Properties& node, const Properties::path_type& path,
            const Type& newValue) {
        return XmlParse::instance().set(node, path, newValue);
    }

    /** 载入json文件 */
    const bool loadJsonFile(const std::string& inputFile);

    /** 保存json文件 */
    void saveJsonFile(const char* outputFile);

    /** 获取json数据 */
    template<typename Type>
    Type jsonData(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return JsonParse::instance().get(path, defaultValue);
    }
    template<typename Type>
    Type jsonData(const Properties& node, const Properties::path_type& path,
            const Type& defaultValue = Type()) {
        return JsonParse::instance().get(node, path, defaultValue);
    }

    /** 设置json数据 */
    template<typename Type>
    void setJsonData(const Properties::path_type& path, const Type& newValue) {
        return JsonParse::instance().set(path, newValue);
    }
    template<typename Type>
    void setJsonData(const Properties& node, const Properties::path_type& path,
            const Type& newValue) {
        return JsonParse::instance().set(node, path, newValue);
    }

private:
    explicit DiskIO();

};

} } // GreenLeaf::GLDiskIO

#endif // GLDISKIO_H

