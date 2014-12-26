/**
 * @file Logger.cpp
 * @brief 日志工具的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "GreenLeaf/GLUtils/Datatime.h"
#include "GreenLeaf/GLUtils/Logger.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建Logger的单例对象
 * @return 返回Logger对象
 */
Logger& Logger::instance()
{
    static Logger _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化Logger对象
 */
Logger::Logger() :
        _level(LL_TRACE),
        _out(NULL)
{
}

/**
 * @brief 初始化Logger
 * @param lev 指定日志等级
 * @param out 指定输出流
 */
void Logger::init(const LoggerLevel& lev, std::ostream* out)
{
    _level = lev;
    _out = out;
}

/**
 * @brief 重新设置输出流
 * @param out 指定输出流
 */
void Logger::resetOut(std::ostream* out) {
    std::ofstream* tmp = dynamic_cast<std::ofstream*>(_out);
    if (NULL != tmp)
        tmp->close();

    _out = out;
}

/**
 * @brief 重新设置日志等级
 * @param lev 指定日志等级
 */
void Logger::resetLevel(const LoggerLevel& lev)
{
    _level = lev;
}

/**
 * @brief 转换日志等级为串
 * @param lev 指定等级
 * @return 返回日志等级串
 */
std::string Logger::levelToString(const LoggerLevel& lev)
{
    switch (lev) {
    case LL_TRACE:
        return "TRACE";
    case LL_DEBUG:
        return "DEBUG";
    case LL_INFO:
        return "INFO";
    case LL_WARN:
        return "WARN";
    default:
        return "ERROR";
    }
}

/**
 * @brief 写入日志
 * @param lev 指定日志等级
 */
void Logger::writeDateStr(const LoggerLevel& lev)
{
    if (NULL != _out)
        *_out << Datatime::instance().localDatatimeFTZ().c_str() <<
        " [" << std::right << std::setw(5) << levelToString(lev) << "] ";
}

} } // GreenLeaf::GLUtils

