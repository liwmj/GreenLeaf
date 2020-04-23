/**
 * @file ParseRequestData.cpp
 * @brief 解析数据的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
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

/**
 * @brief 初始化ParseRequestData对象
 */
ParseRequestData::ParseRequestData():
        _requestBuffer(new RequestBuffer),
        _bodySize(0),
        _leaveBodySize(0)
{
    _requestBuffer->_reqStatus = REQ_NONE;
}

/**
 * @brief 解析原始数据
 * @param data 原始数据
 * @param dataSize 数据大小
 */
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

/**
 * @brief 解析命令行数据
 * @param data 原始数据
 * @param dataSize 原始数据大小
 * @param dataIndex 数据下标
 * @param lineData 单行数据
 * @return 返回解析数据是否成功
 */
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

/**
 * @brief 解析prop数据
 * @param data 原始数据
 * @param dataSize 原始数据大小
 * @param dataIndex 数据下标
 * @param lineData 行数据
 * @return 返回解析数据是否成功
 */
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

/**
 * @brief 解析body数据
 * @param data 原始数据
 * @param dataSize 数据大小
 * @param dataIndex 数据下标
 * @return 返回解析数据是否成功
 */
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

/**
 * @brief 解析数据完成后的处理
 * @param data 原始数据
 * @param dataSize 数据大小
 * @param dataIndex 数据下标
 * @return 返回处理是否成功
 */
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

/**
 * @brief 解析行数据
 * @param data 原始数据
 * @param dataSize 数据大小
 * @param dataIndex 数据下标
 * @param lineData 行数据
 * @return 返回解析是否成功
 */
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

/**
 * @brief 操作行数据
 * @param lineData 行数据
 * @return 返回操作是否成功
 */
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

/**
 * @brief 判断是否为其他命令
 * @return 返回判断结果
 */
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

/**
 * @brief 判断是否有body数据
 * @return 返回判断结果
 */
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

/**
 * @brief 设置methon数据
 * @param methon 具体数据
 */
void ParseRequestData::setMethon(const std::string& methon)
{
    _requestBuffer->_methon = methon;
}

/**
 * @brief 设置params数据
 * @param lineDataSubstr 子串数据
 */
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

/**
 * @brief 设置prop数据
 * @param key prop的键
 * @param value prop的值
 */
void ParseRequestData::setPropItem(std::string& key, const std::string& value)
{
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    // TODO value.substr
//    value.substr(value.find_first_not_of(" "), std::string::npos);

    if (value.empty())
        return ;

    _requestBuffer->_props.insert(std::make_pair(key, value));
}

/**
 * @brief 设置加密版本的prop数据
 * @param enPropKey prop的键
 * @param enPropValue prop的值
 */
void ParseRequestData::setEnPropItem(const std::string& enPropKey,
        const std::string& enPropValue)
{
    _requestBuffer->_enPropKeys.push_back(enPropKey);
    _requestBuffer->_enPropValues.push_back(enPropValue);
}

/**
 * @brief 获取prop的某个值
 * @param key prop的键
 * @return 返回prop的某个值
 */
const std::string ParseRequestData::propValue(std::string key)
{
    PropMap::iterator it = _requestBuffer->_props.find(key);

    if (it != _requestBuffer->_props.end())
        return it->second;

    return std::string();
}

/**
 * @brief 获取prop的某个值并转换成int
 * @param key prop的键
 * @return 返回prop的某个值得int数值
 */
const std::size_t ParseRequestData::propValueToInt(std::string key)
{
    std::string propValue = this->propValue(key);

    return std::atoi(propValue.c_str());
}

} } // GreenLeaf::GLNetIO

