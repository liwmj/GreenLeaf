/*
 * HandlerCommon.h
 *
 *  Created on: Nov 13, 2014
 *      Author: Mason
 */

#ifndef HANDLERCOMMON_H
#define HANDLERCOMMON_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/GLUtils.h"
#include "GreenLeaf/GLNetIO.h"
#include "GreenLeaf/GLDBIO.h"

#include "GreenLeaf/MsgServer/ExceptionCode.h"
#include "GreenLeaf/MsgServer/DataCache.h"
#include "GreenLeaf/MsgServer/UserManager.h"
#include "GreenLeaf/MsgServer/HandlerDefines.h"

namespace GreenLeaf {
namespace Server {

class HandlerCommon
{
public:
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg) = 0;

protected:
    virtual void operationNormal() {}
    virtual void operationException() {}
    virtual void bundleMessage() = 0;
    virtual void bundleErrorMessage() = 0;

    void sendResponseMessage() {
        if (_exceptionCode != 0) {
            this->operationException();

        } else {
            this->operationNormal();
        }
    }

    explicit HandlerCommon();
    virtual ~HandlerCommon();

    void initResponseBufferOperation();

    void setMethon(std::string& methon, const std::string& methonSrc);
    void setParamItem(std::vector<std::string>& params,
            const std::string& paramItem);
    void setPropItem(std::map<std::string, std::string>& map,
            std::string key,
            const std::string& value);
    void setTmpDataItem(std::string key, const std::string value);

    const std::string paramItem(const std::vector<std::string>& params,
            const std::size_t index);
    const std::string propValue(std::map<std::string, std::string>& map,
            std::string key);
    const std::size_t propValueToInt(std::map<std::string, std::string>& map,
            std::string key);
    const std::string tmpDataValue(std::string key);
    const std::size_t tmpDataValueToInt(std::string key);

protected:
    typedef std::map<std::string, std::string> OtherTmpDataMap;
    typedef boost::shared_ptr<OtherTmpDataMap> OtherTmpDataPtr;

    GLUtils::Utils& _utils;
    GLNetIO::NetIO& _netIO;
    GLDBIO::DBIO& _dbIO;
    UserManager& _userManager;

    GLNetIO::ResponseBufferPtr _responseBuffer;
    DataCachePtr _dataCache;
    OtherTmpDataPtr _tmpData;

    std::size_t _exceptionCode;

};

} } // GreenLeaf::Server

#endif // HANDLERCOMMON_H

