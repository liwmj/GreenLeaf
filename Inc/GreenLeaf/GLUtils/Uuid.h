/**
 * @file Uuid.h
 * @brief uuid工具的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef UUID_H
#define UUID_H

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief uuid类
 */
class Uuid: private boost::noncopyable
{
public:
    static Uuid& instance();

    const std::string randUuidToString();
    const std::string randUuidToStringWithBraces();


private:
    boost::uuids::random_generator _rgen;   /**< 随机种子 */

};

} } // GreenLeaf::GLUtils

#endif // UUID_H

