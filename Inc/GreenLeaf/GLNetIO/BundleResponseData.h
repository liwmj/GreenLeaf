/**
 * @file BundleResponseData.h
 * @brief 打包应答数据的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef BUNDLERESPONSEDATA_H
#define BUNDLERESPONSEDATA_H

#include <string>
#include <sstream>

#include <boost/thread/mutex.hpp>

#include "GreenLeaf/GLNetIO/MessageProtocol.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 打包应答数据类
 */
class BundleResponseData
{
public:
    explicit BundleResponseData();

    const std::string bundleAllData(ResponseBufferPtr data);

private:
    void writeMethonData(ResponseBufferPtr data);
    void writeParamsData(ResponseBufferPtr data);
    void writePropsData(ResponseBufferPtr data);

private:
    std::ostringstream _allData;    /**< 打包数据所需流 */

};


} } // GreenLeaf::GLNetIO

#endif // BUNDLERESPONSEDATA_H

