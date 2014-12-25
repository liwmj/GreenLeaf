/*
 * HandlerCommon.cpp
 *
 *  Created on: Nov 13, 2014
 *      Author: wim
 */

#include <iostream>
#include <algorithm>

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

HandlerCommon::HandlerCommon():
        _utils(GLUtils::Utils::instance()),
        _netIO(GLNetIO::NetIO::instance()),
        _dbIO(GLDBIO::DBIO::instance()),
        _userManager(UserManager::instance()),
        _responseBuffer(new GLNetIO::ResponseBuffer),
        _dataCache(new DataCache),
        _tmpData(new OtherTmpDataMap),
        _exceptionCode(0)
{
}

HandlerCommon::~HandlerCommon()
{
}

void HandlerCommon::initResponseBufferOperation()
{
    _responseBuffer->_methon.clear();
    _responseBuffer->_params.clear();
    _responseBuffer->_props.clear();
    _exceptionCode = 0;
}

const std::string HandlerCommon::tmpDataValue(std::string key)
{
    std::map<std::string, std::string>::iterator it = _tmpData->find(key);
    if (it != _tmpData->end())
        return it->second;

    return std::string();
}

const std::size_t HandlerCommon::tmpDataValueToInt(std::string key)
{
    std::string propValue = this->tmpDataValue(key);

    return atoi(propValue.c_str());
}

const std::string HandlerCommon::paramItem(const std::vector<std::string>& params,
        const std::size_t index)
{
    if (index >= params.size())
        return std::string();

    return params.at(index);
}

const std::string HandlerCommon::propValue(std::map<std::string, std::string>& map,
        std::string key)
{
    std::map<std::string, std::string>::iterator it = map.find(key);
    if (it != map.end())
        return it->second;

    return std::string();
}

const std::size_t HandlerCommon::propValueToInt(std::map<std::string, std::string>& map,
        std::string key)
{
    std::string propValue = this->propValue(map, key);

    return std::atoi(propValue.c_str());
}

void HandlerCommon::setMethon(std::string& methon,
        const std::string& methonSrc)
{
    methon = methonSrc;
}

void HandlerCommon::setParamItem(std::vector<std::string>& params,
         const std::string& paramItem)
{
    if (paramItem.empty())
        return ;
    params.push_back(paramItem);
}

void HandlerCommon::setPropItem(std::map<std::string, std::string>& props,
        std::string key,
        const std::string& value)
{
    if (value.empty())
        return ;

    props.insert(std::make_pair(key, value));
}
void HandlerCommon::setTmpDataItem(std::string key,
        std::string value)
{
    if (value.empty())
        return ;

    _tmpData->insert(std::make_pair(key, value));
}


} } // GreenLeaf::Server
