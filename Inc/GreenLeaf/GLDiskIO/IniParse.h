/**
 * @file IniParse.h
 * @brief ini解析的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef INIPARSE_H
#define INIPARSE_H

#include <boost/noncopyable.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace GreenLeaf {
namespace GLDiskIO {

/**
 * @brief ini解析类
 */
class IniParse
{
public:
    typedef boost::property_tree::ptree Properties;

    static IniParse& instance();

    bool loadFile(const std::string& inputFile);
    void saveFile(const char* outputFile);

    template<typename Type>
    Type get(const Properties::path_type& path, const Type& defaultValue =
            Type()) {
        return _properties.get(path, defaultValue);
    }

    template<typename Type>
    Type get(const Properties& node, const Properties::path_type& path,
            const Type& defaultValue = Type()) {
        return node.get(path, defaultValue);
    }

    template<typename Type>
    void set(const Properties::path_type& path, const Type& newValue) {
        return _properties.put(path, newValue);
    }

    template<typename Type>
    void set(const Properties& node, const Properties::path_type& path,
            const Type& newValue) {
        return node.put(path, newValue);
    }

    template<typename Type>
    void add(const Properties::path_type& path, const Type& value) {
        _properties.add(path, value);
    }

    std::size_t remove(const Properties::key_type& key);

    const Properties& getChild(const Properties::path_type& path) const;
    Properties& getChild(const Properties::path_type& path);

private:
    explicit IniParse();

private:
    Properties _properties;     /**< 操作ini所需容器 */

};

} } // GreenLeaf::GLDiskIO

#endif // INIPARSE_H

