/*
 * GLUtils.h
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
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

enum EncryptType {
    ET_ATEN = 0,
    ET_MD5,
    ET_MD5EX
};

class GLUTILS_SHARED_EXPORT Utils: private boost::noncopyable
{
public:
    static Utils& instance();

    void setThreadNumber(const std::size_t& num);
    const std::size_t threadNumber() const;
    boost::asio::io_service& ioService() const;

    void run() const;
    void stop() const;

    const std::string randUuidToString() const;
    const std::string randUuidToStringWithBraces() const;

    const std::string localDatatimeF() const;
    const std::string localDatatimeT() const;
    const std::string localDatatimeFT() const;
    const std::string localDatatimeFTZ() const;

    const std::string& currentPath() const;
    const bool createPaths(const std::string& path) const;
    const std::vector<std::string> splitString(const std::string& src,
            const std::string token);

    void md5Encrypt(std::string& strData);
    void md5exEncrypt(std::string& strData);
    void atenEncrypt(std::string& strA, const char* strKey);
    bool atenDecrypt(std::string& strA, const char* strKey);

    void initLogger(const LoggerLevel& lev, std::ostream* out) const;
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

