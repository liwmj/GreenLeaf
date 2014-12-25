/*
 * ActiveTcpConnection.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#ifndef ACTIVETCPCONNECTION_H
#define ACTIVETCPCONNECTION_H

#include "GreenLeaf/GLUtils.h"

#include "GreenLeaf/GLNetIO/TcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

class ActiveTcpConnection: public TcpConnection
{
public:
    ActiveTcpConnection(boost::asio::io_service& service, const std::string& id,
            const std::string& serverIp, unsigned short serverPort);

    void connect();

private:
    void handleConnect(const boost::system::error_code& error);

private:
    GLUtils::Utils& _utils;
    const std::string _serverIp;
    unsigned short _serverPort;

};
typedef boost::shared_ptr<ActiveTcpConnection> ActiveTcpConnectionPtr;

} } // GreenLeaf::GLNetIO

#endif // ACTIVETCPCONNECTION_H

