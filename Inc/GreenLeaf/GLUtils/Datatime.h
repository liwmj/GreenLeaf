/**
 * @file Datatime.h
 * @brief 日期时间的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef DATATIME_H
#define DATATIME_H

#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 日期时间类
 */
class Datatime: private boost::noncopyable
{
public:
    static Datatime& instance();

    const std::string localDatatimeF();
    const std::string localDatatimeT();
    const std::string localDatatimeFT();
    const std::string localDatatimeFTZ();

private:
    explicit Datatime();

};

} } // GreenLeaf::GLUtils

#endif // DATATIME_H

