/*
 * Connections.h
 *
 *  Created on: Nov 5, 2014
 *      Author: wim
 */

#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <map>
#include <boost/thread/mutex.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "GreenLeaf/GLNetIO/TcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

typedef std::map<std::string, TcpConnectionPtr> TcpConnectionPtrMap;

class Connections: public boost::enable_shared_from_this<Connections>
{
public:
    const TcpConnectionPtrMap& tcpConnectionPtrMap() const;

    TcpConnectionPtr connection(const std::string connectionType);
    void addConnection(const std::string connectionType, TcpConnectionPtr conn);
    void removeConnection(const std::string connectionType);
    void removeCheckConnection(TcpConnectionPtr connection);
    void modifyConnection(const std::string connectionType, TcpConnectionPtr conn);

private:
    typedef boost::asio::ip::tcp tcp;

    TcpConnectionPtrMap _tcpConnectionPtrMap;

};
typedef boost::shared_ptr<Connections> ConnectionsPtr;

} } // GreenLeaf::GLNetIO

#endif // CONNECTIONS_H

