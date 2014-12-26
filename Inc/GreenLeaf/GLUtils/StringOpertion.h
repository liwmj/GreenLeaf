/**
 * @file StringOpertion.h
 * @brief 字符串操作的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef STRINGOPERTION_H
#define STRINGOPERTION_H

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 字符串操作类
 */
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

