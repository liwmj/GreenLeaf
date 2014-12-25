/*
 * StringOpertion.cpp
 *
 *  Created on: Dec 23, 2014
 *      Author: wim
 */

#include <iostream>

#include "GreenLeaf/GLUtils/StringOpertion.h"

namespace GreenLeaf {
namespace GLUtils {

StringOperation& StringOperation::instance()
{
    static StringOperation _gInstance;
    return _gInstance;
}

StringOperation::StringOperation()
{
}

const std::vector<std::string> StringOperation::splitString(const std::string& src,
        const std::string token)
{
    std::vector<std::string> vecRes;

    if (src.empty())
        return vecRes;

    std::string dest;
    std::string tmpSrc(src);
    std::size_t operationIndex = 0;
    std::size_t endIndex = 0;
    std::size_t srcSize = src.size();
    bool isEnd = false;

    while (!isEnd) {
        operationIndex = tmpSrc.find(token);

        if (operationIndex != -1) {
            dest = tmpSrc.substr(0, operationIndex++);
            tmpSrc = tmpSrc.substr(operationIndex, srcSize);
            endIndex += operationIndex;

        } else {
            if (!isEnd) {
                dest = src.substr(endIndex, srcSize);
                isEnd = true;
            }
        }

        vecRes.push_back(dest);
    }

    return vecRes;
}

} } // GreenLeaf::GLUtils

