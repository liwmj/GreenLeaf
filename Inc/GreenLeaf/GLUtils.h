/**
 * @file GLUtils.h
 * @brief GLUtils库的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef GLUTILS_H
#define GLUTILS_H

#if defined(__WIN32__)
	#if defined(GLUTILS_LIBRARY)
	#  define GLUTILS_SHARED_EXPORT __declspec(dllexport)
	#else
	#  define GLUTILS_SHARED_EXPORT __declspec(dllimport)
	#endif
#else
	#define GLUTILS_SHARED_EXPORT
#endif

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>

#include "GreenLeaf/GLUtils/Logger.h"

namespace GreenLeaf {
namespace GLUtils {

/** 加密类型枚举 */
enum EncryptType {
    ET_ATEN = 0,    /**< aten加密 */
    ET_MD5,         /**< md5机密 */
    ET_MD5EX        /**< md5ex加密 */
};

/**
 * @brief GLUtils库的接口类
 */
class GLUTILS_SHARED_EXPORT Utils: private boost::noncopyable
{
public:
    /** GLUtils库的单例接口 */
    static Utils& instance();

    /** 设置工作线程数 */
    void setThreadNumber(const std::size_t& num);

    /** 获取工作线程数 */
    const std::size_t threadNumber() const;

    /** 获取一个io */
    boost::asio::io_service& ioService() const;

    /** 运行所有io */
    void run() const;

    /** 停止所有io */
    void stop() const;

    /** 获取uuid的串值 */
    const std::string randUuidToString() const;

    /** 获取包含花括号的uuid串值 */
    const std::string randUuidToStringWithBraces() const;

    /** 获取本地日期时间 */
    const std::string localDatatimeF() const;
    const std::string localDatatimeT() const;
    const std::string localDatatimeFT() const;
    const std::string localDatatimeFTZ() const;

    /** 获取当前程序路径 */
    const std::string& currentPath() const;

    /** 创建路径所需文件夹 */
    const bool createPaths(const std::string& path) const;

    /** 根据指定字符拆分字符串 */
    const std::vector<std::string> splitString(const std::string& src,
            const std::string token);

    void md5Encrypt(std::string& strData);
    void md5exEncrypt(std::string& strData);
    void atenEncrypt(std::string& strA, const char* strKey);
    bool atenDecrypt(std::string& strA, const char* strKey);

    /**< 初始化日志工具 */
    void initLogger(const LoggerLevel& lev, std::ostream* out) const;

    /**< 传入1-9个参数，写入到日志文件 */
    template<class A1>
    void wirteLog(const LoggerLevel& lev, A1 a1) {
        Logger::instance().log(lev, a1);
    }
    template<class A1, class A2>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2) const {
        Logger::instance().log(lev, a1, a2);
    }
    template<class A1, class A2, class A3>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3) const {
        Logger::instance().log(lev, a1, a2, a3);
    }
    template<class A1, class A2, class A3, class A4>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4) const {
        Logger::instance().log(lev, a1, a2, a3, a4);
    }
    template<class A1, class A2, class A3, class A4, class A5>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const {
        Logger::instance().log(lev, a1, a2, a3, a4, a5);
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
            A6 a6) const {
        Logger::instance().log(lev, a1, a2, a3, a4, a5, a6);
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
            A6 a6, A7 a7) const {
        Logger::instance().log(lev, a1, a2, a3, a4, a5, a6, a7);
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7, class A8>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
            A6 a6, A7 a7, A8 a8) const {
        Logger::instance().log(lev, a1, a2, a3, a4, a5, a6, a7, a8);
    }
    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7, class A8, class A9>
    void wirteLog(const LoggerLevel& lev, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5,
            A6 a6, A7 a7, A8 a8, A9 a9) const {
        Logger::instance().log(lev, a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }

private:
    explicit Utils();

};


} } // GreenLeaf::GLUtils

#endif // GLUTILS_H

