/*
 * DataCacheManager.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#ifndef USERDATACACHEMANAGER_H
#define USERDATACACHEMANAGER_H

#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/MsgServer/DataCache.h"

namespace GreenLeaf {
namespace Server {

class DataCacheManager: private boost::noncopyable
{
public:
    typedef std::map<std::string, DataCache> DataCacheMap;

    static DataCacheManager& instance();

    const std::string dataCacheNumber();

    DataCachePtr dataCache(const std::string& loginName);
    void setDataCache(const std::string& loginName, DataCachePtr userData);

private:
    DataCacheMap _dataCacheMap;
    boost::mutex _mutex;

};

} } // GreenLeaf::Server

#endif // USERDATACACHEMANAGER_H

