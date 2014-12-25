/*
 * GLUtils.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
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

Utils& Utils::instance()
{
    static Utils _gInstance;
    return _gInstance;
}

Utils::Utils()
{
}

void Utils::setThreadNumber(const std::size_t& num)
{
    IOManager::instance().setThreadNumber(num);
}

const std::size_t Utils::threadNumber() const
{
    return IOManager::instance().threadNumber();
}

boost::asio::io_service& Utils::ioService() const
{
    return IOManager::instance().ioService();
}

void Utils::run() const
{
    IOManager::instance().run();
}

void Utils::stop() const
{
    IOManager::instance().stop();
}

const std::string Utils::randUuidToString() const
{
    return Uuid::instance().randUuidToString();
}

const std::string Utils::randUuidToStringWithBraces() const
{
    return Uuid::instance().randUuidToStringWithBraces();
}

const std::string Utils::localDatatimeF() const
{
    return Datatime::instance().localDatatimeF();
}

const std::string Utils::localDatatimeT() const
{
    return Datatime::instance().localDatatimeT();
}

const std::string Utils::localDatatimeFT() const
{
    return Datatime::instance().localDatatimeFT();
}

const std::string Utils::localDatatimeFTZ() const
{
    return Datatime::instance().localDatatimeFTZ();
}

const std::string& Utils::currentPath() const
{
    return Path::instance().currentPath();
}

const bool Utils::createPaths(const std::string& path) const
{
    return Path::instance().createPaths(path);
}

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

void Utils::initLogger(const LoggerLevel& lev, std::ostream* out) const
{
    Logger::instance().init(lev, out);
}

} } // GreenLeaf::GLUtils

