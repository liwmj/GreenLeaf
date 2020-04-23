/**
 * @file Path.h
 * @brief 路径工具类的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef PATH_H
#define PATH_H

#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 路径工具类
 */
class Path: private boost::noncopyable
{
public:
    static Path& instance();

    const std::string& currentPath() const;
    const bool createPaths(const std::string& path) const;

};

} } // GreenLeaf::GLUtils

#endif // PATH_H

