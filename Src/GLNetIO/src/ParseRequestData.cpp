/*
 * ParseRequestData.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: wim
 */

#include <cstring>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <algorithm>

#include "GreenLeaf/GLNetIO/ParseRequestData.h"

using namespace std;

namespace GreenLeaf {
namespace GLNetIO {

ParseRequestData::ParseRequestData():
        _requestBuffer(new RequestBuffer),
        _bodySize(0),
        _leaveBodySize(0)
{
    _requestBuffer->_reqStatus = REQ_NONE;
}

void ParseRequestData::parseAllData(const char* data, const std::size_t& dataSize)
{
    std::size_t dataIndex = 0;
    std::string lineData;

    while (dataSize > dataIndex) {
        if (_requestBuffer->_reqStatus == REQ_NONE) {
            _requestBuffer->_reqStatus = REQ_CMDLINE;
        }

        if (_requestBuffer->_reqStatus == REQ_CMDLINE) {
            if (!this->readCmdData(data, dataSize, dataIndex, lineData))
                return ;
        }

        if (_requestBuffer->_reqStatus == REQ_PROP) {
            if (!this->readPropData(data, dataSize, dataIndex, lineData))
                return ;
        }

        if (_requestBuffer->_reqStatus == REQ_BODY) {
            if (!this->readBodyData(data, dataSize, dataIndex))
                return ;
        }

        if (_requestBuffer->_reqStatus == REQ_DONE) {
            if (!this->readDataDone(data, dataSize, dataIndex))
                return ;
        }
    }
}

const bool ParseRequestData::readCmdData(const char* data,
        const std::size_t& dataSize,
        std::size_t& dataIndex,
        std::string& lineData)
{
    if (this->lineData(data, dataSize, dataIndex, lineData)) {
        if (lineData.length() > 0) {
            if (!this->processLineData(lineData)) {
                _bufferLine.clear();
                _requestBuffer->_reqStatus = REQ_ERROR;
                return false;
            }
            _requestBuffer->_reqStatus = REQ_PROP;
        }

    } else if (this->isOtherCmd()) {
        // TODO otherCmd

    } else {
        return false;

    }

    return true;
}

const bool ParseRequestData::readPropData(const char* data,
        const std::size_t& dataSize,
        std::size_t& dataIndex,
        std::string& lineData)
{
    while (this->lineData(data, dataSize, dataIndex, lineData)) {
        if (lineData.length() > 0) {
            if (!this->processLineData(lineData)) {
                return false;
            }

        } else {
            // TODO PostProcessProp
            _requestBuffer->_reqStatus = REQ_BODY;
            break;
        }

    }

    if (lineData.length() == 0)
        _requestBuffer->_reqStatus = REQ_BODY;

    if (_requestBuffer->_reqStatus == REQ_BODY) {
        if (!this->isCmdHaveBody()) {
            _requestBuffer->_reqStatus = REQ_DONE;
        }

    }
    return true;
}

const bool ParseRequestData::readBodyData(const char* data,
        const std::size_t& dataSize,
        std::size_t& dataIndex)
{
    std::size_t currentBodySize = dataSize - dataIndex;
    std::string bodyData(data);
    bodyData = bodyData.substr(dataIndex);

    if (0 == _leaveBodySize)
        _leaveBodySize = _bodySize;

    if (_leaveBodySize < currentBodySize) {
        _requestBuffer->_reqStatus = REQ_ERROR;
        return false;

    } else {
        dataIndex = dataSize;
        _leaveBodySize -= currentBodySize;
        _requestBuffer->_body += bodyData;

        if (_leaveBodySize > currentBodySize) {
            _requestBuffer->_reqStatus = REQ_BODY;
            return false;

        } else {
            if (_requestBuffer->_body.length() != _bodySize) {
                _requestBuffer->_reqStatus = REQ_BODY;
                return false;
            }
            _requestBuffer->_reqStatus = REQ_DONE;
        }
    }

    return true;
}

const bool ParseRequestData::readDataDone(const char* data,
        const std::size_t& dataSize,
        std::size_t& dataIndex)
{
    if (this->propValueToInt("isstrcmd") == 1) {
        const char* tmpData = data;
        if (tmpData[dataIndex] == '\0')
            ++dataIndex;
    }

    if (dataSize < dataIndex) {
        return false;
    }

    return true;
}

const bool ParseRequestData::lineData(const char* data,
        const std::size_t& dataSize,
        std::size_t& dataIndex,
        std::string& lineData)
{
    bool lineEnd = false;
    std::string tmpData(data);
    lineData.clear();
    while (dataIndex < dataSize && !lineEnd) {
        char ch = tmpData.at(dataIndex);

        switch (ch) {
        case '\r':
            break;
        case '\n':
            lineEnd = true;
            break;
        default:
            _bufferLine.push_back(ch);
            break;
        }
        ++dataIndex;
    }
    if (lineEnd) {
        lineData.assign(_bufferLine.begin(), _bufferLine.end());
        _bufferLine.clear();
    }

    return lineEnd;
}

const bool ParseRequestData::processLineData(std::string& lineData)
{
    std::size_t operateIndex = 0;

    if (_requestBuffer->_reqStatus == REQ_NONE) {
        _requestBuffer->_reqStatus = REQ_CMDLINE;
    }

    if (_requestBuffer->_reqStatus == REQ_CMDLINE) {
        operateIndex = lineData.find(' ');
        if (operateIndex != -1) {
            this->setMethon(lineData.substr(0, operateIndex));
            this->setParams(lineData.substr(operateIndex + 1,
                    lineData.length() - (operateIndex + 1)));

        } else {
            this->setMethon(lineData);

        }
    }

    if (_requestBuffer->_reqStatus == REQ_PROP) {
        operateIndex = lineData.find(':');
        if (operateIndex != -1) {
            std::string key = lineData.substr(0, operateIndex);
            std::string value;

            if (key.empty())
                return false;

            if (key.at(0) == '*') {
                value = lineData.substr(0, operateIndex + 1);
                key = key.substr(1);

                this->setEnPropItem(key, value);

            } else {
                value = lineData.substr(operateIndex + 1,
                        lineData.length() - (operateIndex + 1));
                this->setPropItem(key, value);

            }

            std::transform(key.begin(), key.end(), key.begin(), ::tolower);
            // TODO beginpos
            if (key.compare(("beginpos")) == 0) {}

        } else {
            return false;

        }
    }

    return true;
}

const bool ParseRequestData::isOtherCmd() const
{
    if (_bufferLine.empty())
        return false;
    if (_bufferLine.size() <= 0)
        return false;
    if (_bufferLine.at(_bufferLine.size() - 1) != '\0')
        return false;
    if (_bufferLine.at(0) != '<')
        return false;

    if (std::string().assign(_bufferLine.begin(), _bufferLine.end())
            == "<policy-file-request/>") {
        return true;
    } else {
        return false;
    }
}

const bool ParseRequestData::isCmdHaveBody()
{
    bool isHaveBody = false;
    std::string strValue = this->propValue("content-length");

    if (!strValue.empty()) {
        _bodySize = std::atoi(strValue.c_str());
        isHaveBody = true;

    } else {
        _bodySize = 0;

    }

    if(_bodySize <= 0)
        return false;

    return isHaveBody;
}

void ParseRequestData::setMethon(const std::string& methon)
{
    _requestBuffer->_methon = methon;
}

void ParseRequestData::setParams(const std::string& lineDataSubstr)
{
    _requestBuffer->_params.clear();

    std::string paramItem;
    std::size_t tmpBegin = 0;
    std::size_t tmpPos = 0;
    bool isEnd = false;

    do {
        tmpPos  = lineDataSubstr.find(' ', tmpBegin);
        paramItem.clear();
        if (tmpPos >= 0) {
            paramItem = lineDataSubstr.substr(tmpBegin, tmpPos - tmpBegin);

        } else {
            paramItem = lineDataSubstr.substr(tmpBegin, lineDataSubstr.length() - tmpBegin);
            isEnd = true;

        }

        _requestBuffer->_params.push_back(paramItem);

        if(tmpPos == -1)
            break;
        tmpBegin = tmpPos + 1;

    } while (!isEnd);

}

void ParseRequestData::setPropItem(std::string& key, const std::string& value)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    // TODO value.substr
//    value.substr(value.find_first_not_of(" "), std::string::npos);

    if (value.empty())
        return ;

    _requestBuffer->_props.insert(std::make_pair(key, value));
}

void ParseRequestData::setEnPropItem(const std::string& enPropKey,
        const std::string& enPropValue)
{
    _requestBuffer->_enPropKeys.push_back(enPropKey);
    _requestBuffer->_enPropValues.push_back(enPropValue);
}

const std::string ParseRequestData::propValue(std::string key)
{
    PropMap::iterator it = _requestBuffer->_props.find(key);

    if (it != _requestBuffer->_props.end())
        return it->second;

    return std::string();
}

const std::size_t ParseRequestData::propValueToInt(std::string key)
{
    std::string propValue = this->propValue(key);

    return std::atoi(propValue.c_str());
}

} } // GreenLeaf::GLNetIO

