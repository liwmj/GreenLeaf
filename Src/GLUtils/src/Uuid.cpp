/**
 * @file Uuid.cpp
 * @brief uuid的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include "GreenLeaf/GLUtils/Uuid.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建Uuid的单例对象
 * @return 返回Uuid对象
 */
Uuid& Uuid::instance()
{
    static Uuid _gInstance;
    return _gInstance;
}

/**
 * @brief 获取uuid的串值
 * @return 返回uuid的串值
 */
const std::string Uuid::randUuidToString()
{
    return boost::lexical_cast<std::string>(_rgen());
}

/**
 * @brief 获取包含花括号的串值
 * @return 返回包含花括号的串值
 */
const std::string Uuid::randUuidToStringWithBraces()
{
    std::string uuid("{");
    uuid += this->randUuidToString(); uuid += "}";
    return uuid;
}


} } // GreenLeaf::GLUtils

