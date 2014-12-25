/*
 * ConnectionCollection.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: wim
 */

#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/Connections.h"

namespace GreenLeaf {
namespace GLNetIO {

const TcpConnectionPtrMap& Connections::tcpConnectionPtrMap() const
{
    return _tcpConnectionPtrMap;
}

TcpConnectionPtr Connections::connection(const std::string connectionType)
{
    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.find(connectionType);
    return it == _tcpConnectionPtrMap.end() ? TcpConnectionPtr() : it->second;
}

void Connections::addConnection(const std::string connectionType,
        TcpConnectionPtr conn)
{
    if (!conn.get())
        return ;

    _tcpConnectionPtrMap.insert(std::make_pair(connectionType, conn));
    conn->setRemoveCallBack(boost::bind(&Connections::removeCheckConnection, shared_from_this(), conn));
}

void Connections::removeConnection(const std::string connectionType)
{
    _tcpConnectionPtrMap.erase(connectionType);
}

void Connections::removeCheckConnection(TcpConnectionPtr connection)
{
    if (!connection.get())
        return ;

    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.begin();
    for (; it != _tcpConnectionPtrMap.end(); ++it) {
        if (it->second.get()) {
            if (it->second->id() == connection->id()) {
                _tcpConnectionPtrMap.erase(it->first);

            }
        }
    }
}

void Connections::modifyConnection(const std::string connectionType,
        TcpConnectionPtr conn)
{
    if (!conn.get())
        return ;

    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.find(connectionType);
    if (it != _tcpConnectionPtrMap.end()) {
        it->second.reset();
        it->second = conn;
    }
}

} } //GreenLeaf::GLNetIO

