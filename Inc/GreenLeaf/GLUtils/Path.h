/*
 * Path.h
 *
 *  Created on: Nov 7, 2014
 *      Author: wim
 */

#ifndef PATH_H
#define PATH_H

#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

class Path: private boost::noncopyable
{
public:
    static Path& instance();

    const std::string& currentPath() const;
    const bool createPaths(const std::string& path) const;

};

} } // GreenLeaf::GLUtils

#endif // PATH_H

