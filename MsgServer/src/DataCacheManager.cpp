/*
 * DataCacheManager.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: Mason
 */

#include <boost/format.hpp>

#include "GreenLeaf/MsgServer/DataCacheManager.h"

namespace GreenLeaf {
namespace Server {

DataCacheManager& DataCacheManager::instance()
{
    static DataCacheManager _gInstance;
    return _gInstance;
}

const std::string DataCacheManager::dataCacheNumber()
{
    boost::mutex::scoped_lock lock(_mutex);
    return boost::str(boost::format("%d") % _dataCacheMap.size());
}

DataCachePtr DataCacheManager::dataCache(const std::string& loginName)
{
    boost::mutex::scoped_lock lock(_mutex);
    DataCacheMap::iterator it = _dataCacheMap.find(loginName);

    return it == _dataCacheMap.end() ? DataCachePtr() : DataCachePtr(new DataCache(it->second));
}

void DataCacheManager::setDataCache(const std::string& loginName, DataCachePtr userData)
{
    boost::mutex::scoped_lock lock(_mutex);
    _dataCacheMap.insert(std::make_pair(loginName, *userData));
}

} } // GreenLeaf::Server

