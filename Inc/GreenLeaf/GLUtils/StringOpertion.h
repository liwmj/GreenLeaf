/*
 * StringOpertion.h
 *
 *  Created on: Dec 23, 2014
 *      Author: wim
 */

#ifndef STRINGOPERTION_H
#define STRINGOPERTION_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

class StringOperation: private boost::noncopyable
{
public:
    static StringOperation& instance();

    const std::vector<std::string> splitString(const std::string& src,
            const std::string token);

private:
    explicit StringOperation();
};

} } // GreenLeaf::GLUtils

#endif // STRINGOPERTION_H

