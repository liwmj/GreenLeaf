/**
 * @file GLUtils.cpp
 * @brief GLUtils库的接口实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <string>
#include <vector>

#include "GreenLeaf/GLUtils/IOManager.h"
#include "GreenLeaf/GLUtils/Uuid.h"
#include "GreenLeaf/GLUtils/Datatime.h"
#include "GreenLeaf/GLUtils/Path.h"
#include "GreenLeaf/GLUtils/StringOpertion.h"
#include "GreenLeaf/GLUtils/ATENEncryption.h"
#include "GreenLeaf/GLUtils/MD5Encryption.h"

#include "GreenLeaf/GLUtils.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建Utils的单例对象
 * @return 返回Utils对象
 */
Utils& Utils::instance()
{
    static Utils _gInstance;
    return _gInstance;
}

/**
 * @brief 析构Utils对象
 */
Utils::Utils()
{
}

/**
 * @brief 设置工作线程数
 * @param num 指定线程数
 */
void Utils::setThreadNumber(const std::size_t& num)
{
    IOManager::instance().setThreadNumber(num);
}

/**
 * @brief 获取工作线程数
 * @return 返回工作线程数
 */
const std::size_t Utils::threadNumber() const
{
    return IOManager::instance().threadNumber();
}

/**
 * @brief 获取一个io
 * @return 返回一个io
 */
boost::asio::io_service& Utils::ioService() const
{
    return IOManager::instance().ioService();
}

/**
 * @brief 运行所有io
 */
void Utils::run() const
{
    IOManager::instance().run();
}

/**
 * @brief 停止所有io
 */
void Utils::stop() const
{
    IOManager::instance().stop();
}

/**
 * @brief 获取uuid的字符串
 * @return 返回uuid的字符串
 */
const std::string Utils::randUuidToString() const
{
    return Uuid::instance().randUuidToString();
}

/**
 * @brief 获取带花括号包裹的uuid字符串
 * @return 返回带花括号包裹的uuid字符串
 */
const std::string Utils::randUuidToStringWithBraces() const
{
    return Uuid::instance().randUuidToStringWithBraces();
}

/**
 * @brief 获取本地日期时间
 * @return 返回本地日期时间
 */
const std::string Utils::localDatatimeF() const
{
    return Datatime::instance().localDatatimeF();
}

/**
 * @brief 获取本地日期时间
 * @return 返回本地日期时间
 */
const std::string Utils::localDatatimeT() const
{
    return Datatime::instance().localDatatimeT();
}

/**
 * @brief 获取本地日期时间
 * @return 返回本地日期时间
 */
const std::string Utils::localDatatimeFT() const
{
    return Datatime::instance().localDatatimeFT();
}

/**
 * @brief 获取本地日期时间
 * @return 返回本地日期时间
 */
const std::string Utils::localDatatimeFTZ() const
{
    return Datatime::instance().localDatatimeFTZ();
}

/**
 * @brief 获取当前程序的路径
 * @return 返回单签程序的路径
 */
const std::string& Utils::currentPath() const
{
    return Path::instance().currentPath();
}

/**
 * @brief 创建整个路径所需文件夹
 * @param path 指定路径
 * @return 返回创建是否成功
 */
const bool Utils::createPaths(const std::string& path) const
{
    return Path::instance().createPaths(path);
}

/**
 * @brief 根据字符拆分串
 * @param src 需拆分的串
 * @param token 指定字符
 * @return 返回串数组
 */
const std::vector<std::string> Utils::splitString(const std::string& src,
        const std::string token)
{
    return StringOperation::instance().splitString(src, token);
}

void Utils::md5Encrypt(std::string& strData)
{
    char szEncrypt[33] = {0};

    MD5Encryption::instance().digest_md5((unsigned char*)strData.c_str(),
            strData.length(), (unsigned char*)szEncrypt);

    strData = szEncrypt;
}

void Utils::md5exEncrypt(std::string& strData)
{
//    char szEncrypt[33]   = { 0 };
//    std::string Buffer;
//
//    int nLength = strData.length();
//    char *pchTemp = new char[nLength * 2];
//
//    memcpy( pchTemp, strData.GetBuffer(strData.length()), nLength * 2);
//    strData.ReleaseBuffer(strData.length());
//    MD5Encryption::instance().digest_md5((unsigned char*)pchTemp, nLength*2, (unsigned char *)szEncrypt);
//    CAtStrCode::ANSIToString( szEncrypt );
//
//    strData = szEncrypt;
//    delete[] pchTemp;
}

void Utils::atenEncrypt(std::string& strA, const char* strKey)
{
    ATENEncryption::instance().encrypt(strA, strKey);
}

bool Utils::atenDecrypt(std::string& strA, const char* strKey)
{
    return ATENEncryption::instance().decrypt(strA, strKey);
}

/**
 * @brief 初始化日志工具
 * @param lev 指定日志打印等级
 * @param out 指定输出流
 */
void Utils::initLogger(const LoggerLevel& lev, std::ostream* out) const
{
    Logger::instance().init(lev, out);
}

} } // GreenLeaf::GLUtils

