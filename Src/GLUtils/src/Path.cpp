/*
 * Path.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: wim
 */

#include <boost/filesystem.hpp>

#include "GreenLeaf/GLUtils/Path.h"

namespace GreenLeaf {
namespace GLUtils {

Path& Path::instance()
{
    static Path _gInstance;
    return _gInstance;
}

const std::string& Path::currentPath() const
{
    return boost::filesystem::initial_path().string();
}

const bool Path::createPaths(const std::string& path) const
{
    boost::system::error_code error;
    boost::filesystem::create_directories(path, error);

    if (error)
        return false;

    return true;
}

} } // GreenLeaf::GLUtils

