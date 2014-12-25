/*
 * BundleResponseData.h
 *
 *  Created on: Nov 10, 2014
 *      Author: wim
 */

#ifndef BUNDLERESPONSEDATA_H
#define BUNDLERESPONSEDATA_H

#include <string>
#include <sstream>

#include <boost/thread/mutex.hpp>

#include "GreenLeaf/GLNetIO/MessageProtocol.h"

namespace GreenLeaf {
namespace GLNetIO {

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
    std::ostringstream _allData;

};


} } // GreenLeaf::GLNetIO

#endif // BUNDLERESPONSEDATA_H

