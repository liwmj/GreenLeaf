/**
 * @file Datatime.cpp
 * @brief 日期时间的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "GreenLeaf/GLUtils/Datatime.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建Datatime的单例对象
 * @return 返回Datatime对象
 */
Datatime& Datatime::instance()
{
    static Datatime _gInstance;
    return _gInstance;
}

/**
 * @brief 析构Datatime对象
 */
Datatime::Datatime()
{
}

/**
 * @brief 获取本地日期和时间
 * @return 
 */
const std::string Datatime::localDatatimeF()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F", now);

    return std::string(ds);
}

/**
 * @brief 获取本地日期和时间
 * @return 
 */
const std::string Datatime::localDatatimeT()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%T", now);

    return std::string(ds);
}

/**
 * @brief 获取本地日期和时间
 * @return 
 */
const std::string Datatime::localDatatimeFT()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F %T", now);

    return std::string(ds);
}

/**
 * @brief 获取本地日期和时间
 * @return 
 */
const std::string Datatime::localDatatimeFTZ()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F %T %Z", now);

    return std::string(ds);
}

} } // GreenLeaf::GLUtils

