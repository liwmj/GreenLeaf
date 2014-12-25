/*
 * Uuid.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: wim
 */

#include "GreenLeaf/GLUtils/Uuid.h"

namespace GreenLeaf {
namespace GLUtils {

Uuid& Uuid::instance()
{
    static Uuid _gInstance;
    return _gInstance;
}

const std::string Uuid::randUuidToString()
{
    return boost::lexical_cast<std::string>(_rgen());
}

const std::string Uuid::randUuidToStringWithBraces()
{
    std::string uuid("{");
    uuid += this->randUuidToString(); uuid += "}";
    return uuid;
}


} } // GreenLeaf::GLUtils

