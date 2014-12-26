/**
 * @file BundleResponseData.cpp
 * @brief 打包应答数据的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "GreenLeaf/GLNetIO/BundleResponseData.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 初始化BundleResponseData对象
 */
BundleResponseData::BundleResponseData()
{
}

/**
 * @brief 打包所有需应答的数据
 * @param data 应答数据缓冲区的指针
 * @return 返回打包好的应答数据
 */
const std::string BundleResponseData::bundleAllData(ResponseBufferPtr data)
{
    _allData.str("");

    writeMethonData(data);
    writeParamsData(data);
    writePropsData(data);

    _allData << "\r\n";
    return _allData.str();
}

/**
 * @brief 写入methon数据
 * @param data 应答数据缓冲区的指针
 */
void BundleResponseData::writeMethonData(ResponseBufferPtr data)
{
    _allData << data->_methon;
}

/**
 * @brief 写入params数据
 * @param data 应答数据缓冲区的指针
 */
void BundleResponseData::writeParamsData(ResponseBufferPtr data)
{
    for (int i = 0; i < data->_params.size(); ++i) {
        _allData << " ";
        _allData << data->_params[i];
    }
    _allData << "\r\n";
}

/**
 * @brief 写入props数据
 * @param data 应答数据缓冲区的指针
 */
void BundleResponseData::writePropsData(ResponseBufferPtr data)
{
    PropMap::iterator it = data->_props.begin();
    for (; it != data->_props.end(); ++it) {
        _allData << it->first;
        _allData << ":";
        _allData << it->second;
        _allData << "\r\n";
    }
}

} } // GreenLeaf::GLNetIO

