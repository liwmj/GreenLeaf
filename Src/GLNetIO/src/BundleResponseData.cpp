/*
 * BundleResponse.cpp
 *
 *  Created on: Nov 10, 2014
 *      Author: wim
 */

#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

#include "GreenLeaf/GLNetIO/BundleResponseData.h"

namespace GreenLeaf {
namespace GLNetIO {

BundleResponseData::BundleResponseData()
{
}

const std::string BundleResponseData::bundleAllData(ResponseBufferPtr data)
{
    _allData.str("");

    writeMethonData(data);
    writeParamsData(data);
    writePropsData(data);

    _allData << "\r\n";
    return _allData.str();
}

void BundleResponseData::writeMethonData(ResponseBufferPtr data)
{
    _allData << data->_methon;
}

void BundleResponseData::writeParamsData(ResponseBufferPtr data)
{
    for (int i = 0; i < data->_params.size(); ++i) {
        _allData << " ";
        _allData << data->_params[i];
    }
    _allData << "\r\n";
}

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

