/*
 * Sessions.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#include "GreenLeaf/GLNetIO/Sessions.h"

namespace GreenLeaf {
namespace GLNetIO {

const ConnectionsPtrMap& Sessions::connectionsPtrMap() const
{
    return _connectionsPtrMap;
}

ConnectionsPtr Sessions::session(const std::string sessionType)
{
    ConnectionsPtrMap::iterator it = _connectionsPtrMap.find(sessionType);
    return it == _connectionsPtrMap.end() ? ConnectionsPtr() : it->second;
}

void Sessions::addSession(const std::string sessionType,
        ConnectionsPtr connections)
{
    _connectionsPtrMap.insert(std::make_pair(sessionType, connections));
}

void Sessions::removeSession(const std::string sessionType)
{
    _connectionsPtrMap.erase(sessionType);
}

void Sessions::modifySession(const std::string sessionType,
        ConnectionsPtr connections)
{
    ConnectionsPtrMap::iterator it = _connectionsPtrMap.find(sessionType);
    if (it != _connectionsPtrMap.end()) {
        it->second.reset();
        it->second = connections;
    }
}

} } // GreenLeaf::GLNetIO

