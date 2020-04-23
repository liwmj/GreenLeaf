/**
 * @file Path.cpp
 * @brief 路径工具的实现工具
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/filesystem.hpp>

#include "GreenLeaf/GLUtils/Path.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建Path的单例对象
 * @return 返回Path对象
 */
Path& Path::instance()
{
    static Path _gInstance;
    return _gInstance;
}

/**
 * @brief 获取当前程序路径
 * @return 返回当前程序路径
 */
const std::string& Path::currentPath() const
{
    return boost::filesystem::initial_path().string();
}

/**
 * @brief 创建路径
 * @param path 指定路径
 * @return 返回创建是否成功
 */
const bool Path::createPaths(const std::string& path) const
{
    boost::system::error_code error;
    boost::filesystem::create_directories(path, error);

    if (error)
        return false;

    return true;
}

} } // GreenLeaf::GLUtils

