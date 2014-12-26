/**
 * @file ParseRequestData.h
 * @brief 解析请求数据的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef PARSEREQUESTDATA_H
#define PARSEREQUESTDATA_H

#include <string>
#include <vector>
#include <map>

#include "GreenLeaf/GLNetIO/MessageProtocol.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 解析请求数据类
 */
class ParseRequestData
{
public:
    explicit ParseRequestData();

    void parseAllData(const char* data, const std::size_t& dataSize);

public:
    RequestBufferPtr _requestBuffer;    /**< 请求数据的缓冲区 */

private:
    const bool readCmdData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& lineData);
    const bool readPropData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& lineData);
    const bool readBodyData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex);
    const bool readDataDone(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex);

    const bool lineData(const char* data,
            const std::size_t& dataSize,
            std::size_t& dataIndex,
            std::string& line);
    const bool processLineData(std::string& lineData);
    const bool isOtherCmd() const;
    const bool isCmdHaveBody();

    void setMethon(const std::string& methon);
    void setParams(const std::string& lineDataSubstr);
    void setPropItem(std::string& key, const std::string& value);
    void setEnPropItem(const std::string& enPropkey, const std::string& enPropValue);

    const std::string propValue(std::string key);
    const std::size_t propValueToInt(std::string key);

private:
    std::size_t _bodySize;          /**< body数据的大小 */
    std::size_t _leaveBodySize;     /**< 剩余body数据的大小 */
    std::vector<char> _bufferLine;  /**< 行缓冲数据 */

};

} } // GreenLeaf::GLNetIO

#endif // PARSEREQUESTDATA_H

