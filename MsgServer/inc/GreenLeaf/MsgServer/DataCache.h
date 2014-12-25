/*
 * DataCache.h
 *
 *  Created on: Dec 15, 2014
 *      Author: wim
 */

#ifndef DATACACHE_H
#define DATACACHE_H

#include <string>
#include <boost/shared_ptr.hpp>

namespace GreenLeaf {
namespace Server {

struct DataCache
{
    std::string _id;
    std::string _loginName;
    std::string _name;
    std::string _pword;
    std::string _enType;
    std::string _itemIndex;
    std::string _note;
    std::string _farServer;
    std::string _ipAddr;

    DataCache() {}
    DataCache(const DataCache& dataCache): _id(dataCache._id),
            _loginName(dataCache._loginName),
            _name(dataCache._name),
            _pword(dataCache._pword),
            _enType(dataCache._enType),
            _itemIndex(dataCache._itemIndex),
            _note(dataCache._note),
            _farServer(dataCache._farServer),
            _ipAddr(dataCache._ipAddr) {}
    DataCache& operator=(const DataCache& dataCache) {
        _id = dataCache._id;
        _loginName = dataCache._loginName;
        _name = dataCache._name;
        _pword = dataCache._pword;
        _enType = dataCache._enType;
        _itemIndex = dataCache._itemIndex;
        _note = dataCache._note;
        _farServer = dataCache._farServer;
        _ipAddr = dataCache._ipAddr;
        return *this;
    }
};
typedef boost::shared_ptr<DataCache> DataCachePtr;

} } // GreenLeaf::Server

#endif // DATACACHE_H

