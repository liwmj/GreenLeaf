/*
 * ATENEncryption.h
 *
 *  Created on: Nov 26, 2014
 *      Author: Mason
 */

#ifndef ATENENCRYPTION_H
#define ATENENCRYPTION_H

#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

class ATENEncryption: private boost::noncopyable
{
public:
    static ATENEncryption& instance();

    void encrypt(std::string& strA, const char* strKey);
    bool decrypt(std::string& strA, const char* strKey);

private:
    void getEncryptKey(std::string strKey, std::string& strKey1, std::string& strKey2, std::string& strKey3, std::string& strKey4);
    void encryptAndDecrypt(std::string& str, std::string strKey );
    void operation(std::string& strLeft, std::string& strRight, std::string strKey1, std::string strKey2);
    std::string plus(std::string str, std::string strKey);
    void xOr(std::string& str, std::string strKey);
    void exchange(std::string& strLeft, std::string& strRight );
    int hexStrToDec(std::string str );
    int charToInt(char ch);
};


} } // GreenLeaf::GLUtils

#endif // ATENENCRYPTION_H

