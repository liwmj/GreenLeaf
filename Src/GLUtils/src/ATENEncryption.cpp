/*
 * ATENEncryption.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: Mason
 */

#include <cstdlib>
#include <string>
#include <algorithm>
#include <boost/format.hpp>

#include "GreenLeaf/GLUtils/ATENEncryption.h"

namespace GreenLeaf {
namespace GLUtils {

ATENEncryption& ATENEncryption::instance()
{
    static ATENEncryption _gInstance;
    return _gInstance;
}

void ATENEncryption::encrypt(std::string& str, const char* strKey)
{
    if (str.empty())
        return;

    std::string strTemp;
    std::string strSource;
    int nLeng   = str.length();
    int nSource;

    while(str.length() % 4 != 0) {
        str += '0';
    }

    for (int i = 0; i < str.length(); ++i) {
        nSource = str.at(i);
        if (nSource < 0) {
            nSource += 256;
        }
        strTemp = boost::str(boost::format("%x") % nSource);
        if(1 == strTemp.length()) {
            strTemp.insert(0, "0");
        }
        strSource += strTemp;
    }

    this->encryptAndDecrypt(strSource, strKey);

    strTemp = boost::str(boost::format("%d") % nLeng);
    if (nLeng < 10) {
        strTemp.insert(0, "0");
    }
    str = strSource + strTemp;
}

bool ATENEncryption::decrypt(std::string& str, const char* strKey)
{
    if(str.empty())
        return false;

    std::string strTemp;
    std::string strSource;
    int nLeng;
    int nSource;
    strTemp = str.substr(str.length() - 2, str.length());
    str = str.substr(0, str.length() - 2);
    nLeng = std::atoi(strTemp.c_str());
    if (nLeng <= 0 || str.length() < 8) {
        return false;
    }
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    strTemp = str.substr(0, str.find_first_of("0123456789abcdef"));
    if (strTemp != str) {
        return false;
    }

    this->encryptAndDecrypt(str, strKey);

    strSource = str.substr(0, nLeng * 2);
    str.clear();
    if(strSource.length() != nLeng * 2) {
        return false;
    }

    for (int i = 0; i < nLeng; ++i) {
        strTemp = strSource.substr(i * 2, 2);
        nSource = this->hexStrToDec(strTemp);
        strTemp = boost::str(boost::format("%c") % nSource);
        str += strTemp;
    }

    return true;
}

void ATENEncryption::getEncryptKey(std::string strKey, std::string& strKey1, std::string& strKey2, std::string& strKey3, std::string& strKey4 )
{
    std::string strTemp = strKey;
    std::string strTempKey;
    int nKey;

    while (strKey.length() < 8)
        strKey += strTemp;

    if(strKey.length() > 8) {
        strKey = strKey.substr(0, 8);
    }

    for (int i = 0; i < 8; ++i) {
        nKey = strKey.at(i);
        if(nKey < 0) {
            nKey += 256;
        }
        strTemp = boost::str(boost::format("%x") % nKey);
        strTempKey  += strTemp;
    }

    strTemp = strTempKey.substr(0, 1);
    strTempKey = strTempKey + strTemp;
    strKey = strTempKey.substr(strTempKey.length() - 1, strTempKey.length());

    strKey1 = strKey.substr(0, 4);
    strKey2 = strKey.substr(4, 4);
    strKey3 = strKey.substr(8, 4);
    strKey4 = strKey.substr(12, 4);

}

void ATENEncryption::encryptAndDecrypt(std::string& str, std::string strKey)
{
    std::string strKey1, strKey2, strKey3, strKey4;
    std::string strTemp, strSource = str;
    std::string strLeft, strRight;

    this->getEncryptKey(strKey, strKey1, strKey2, strKey3, strKey4);

    str.clear();
    while (!strSource.empty()) {
        strTemp = strSource.substr(0, 8);
        strSource = strSource.substr(strSource.length() - 8, strSource.length());

        strLeft = strTemp.substr(0, 4);
        strRight = strTemp.substr(strTemp.length() - 4, strTemp.length());

        this->operation(strLeft,strRight,strKey1,strKey2);
        this->exchange( strLeft,strRight );

        this->operation(strLeft,strRight,strKey3,strKey4);
        this->exchange( strLeft,strRight );

        this->operation(strLeft,strRight,strKey4,strKey3);
        this->exchange( strLeft,strRight );

        this->operation(strLeft,strRight,strKey2,strKey1);

        strTemp = strLeft;
        strLeft = strRight;
        strRight = strTemp;

        str = str + strLeft + strRight;
    }
}

void ATENEncryption::operation(std::string& strLeft, std::string& strRight, std::string strKey1, std::string strKey2)
{
    std::string strTemp;

    // strTemp  = strKey1 + strRight
    strTemp = this->plus(strRight, strKey1);

    // strLeft  = strLeft ^ strTemp
    this->xOr(strLeft, strTemp);

    // strTemp  = strKey2 + strLeft
    strTemp = this->plus(strLeft, strKey2);

    // strRight = strRight ^ strTemp
    this->xOr(strRight, strTemp);
}

std::string ATENEncryption::plus(std::string str, std::string strKey)
{
    std::string strResult;
    std::string strTemp;
    int nSource, nKey;
    int nCarry  = 0;

    for (int i = str.length() - 1; i >= 0 ; --i) {
        nSource = this->charToInt(str.at(i));
        nKey = this->charToInt(strKey.at(i));

        nSource = nSource + nKey + nCarry;
        if(nSource >= 16) {
            nSource = nSource - 16;
            nCarry = 1;
        } else {
            nCarry = 0;
        }

        strTemp = boost::str(boost::format("%x") % nSource);
        strResult.insert(0, strTemp);
    }

    return strResult;
}

void ATENEncryption::xOr(std::string& str, std::string strKey)
{
    std::string strTemp, strResult;
    int nSource, nKey;

    for (int i = str.length() - 1; i >= 0; --i) {
        nSource = this->charToInt(str.at(i));
        nKey = this->charToInt(strKey.at(i));

        nSource = nSource ^ nKey;
        strTemp = boost::str(boost::format("%x") % nSource);
        strResult.insert(0, strTemp);
    }
    str = strResult;
}

void ATENEncryption::exchange(std::string& strLeft, std::string& strRight)
{
    std::string strHigh, strLow;
    std::string strTemp = strRight;

    strHigh = strLeft.substr(0, 2);
    strLow = strLeft.substr(strLeft.length() - 2, strLeft.length());
    strRight = strLow + strHigh;

    strHigh = strTemp.substr(0, 2);
    strLow = strTemp.substr(strTemp.length() - 2, strTemp.length());
    strLeft = strLow + strHigh;
}

int ATENEncryption::hexStrToDec(std::string str)
{
    std::string strTemp;
    int nHigh, nLow;
    char chHigh, chLow;

    chHigh = str.at(0);
    chLow = str.at(1);

    nHigh = this->charToInt(chHigh);
    nLow = this->charToInt(chLow);

    return  nHigh * 16 + nLow;
}

int ATENEncryption::charToInt(char ch)
{
    switch (ch) {
    case 'F' :
    case 'f' :
        return 15;
    case 'E' :
    case 'e' :
        return 14;
    case 'D' :
    case 'd' :
        return 13;
    case 'C' :
    case 'c' :
        return 12;
    case 'B' :
    case 'b' :
        return 11;
    case 'A' :
    case 'a' :
        return 10;
    default  :
        return ch - '0';
    }

    return 0;
}

} } // GreenLeaf::GLUtils

