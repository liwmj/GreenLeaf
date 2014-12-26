/**
 * @file StringOpertion.cpp
 * @brief 字符串操作的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>

#include "GreenLeaf/GLUtils/StringOpertion.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建StringOperation的单例对象
 * @return 返回StringOperation对象
 */
StringOperation& StringOperation::instance()
{
    static StringOperation _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化StringOperation对象
 */
StringOperation::StringOperation()
{
}

/**
 * @brief 获取字符串拆分后的串组
 * @param src 指定需拆分串
 * @param token 指定字符
 * @return 返回字符串拆分后的串组
 */
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

