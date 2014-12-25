/*
 * ActiveTcpConnection.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/ActiveTcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

ActiveTcpConnection::ActiveTcpConnection(boost::asio::io_service& service,
        const std::string& id, const std::string& ip, unsigned short port):
                _utils(GLUtils::Utils::instance()),
                TcpConnection(service, id), _serverIp(ip), _serverPort(port)
{
}

void ActiveTcpConnection::connect()
{
    tcp::resolver resolver(this->socket().get_io_service());

    char portStr[8] = "";
    std::sprintf(portStr, "%hd", _serverPort);

    tcp::resolver::query query(_serverIp, portStr);

    boost::system::error_code ec;
    tcp::resolver::iterator iterator = resolver.resolve(query, ec);
    if (ec) {
        _utils.wirteLog(GLUtils::LL_ERROR,
                "Resolver %1%(%2%:%3%): %4%", this->id(), _serverIp, _serverPort,
                ec.message());
        return ;
    }

    _utils.wirteLog(GLUtils::LL_DEBUG,
            "Resolved %1%(%2%:%3%): %4%:%5%", this->id(), _serverIp, _serverPort,
            iterator->endpoint().address(), iterator->endpoint().port());

    this->socket().async_connect(*iterator,
            boost::bind(&ActiveTcpConnection::handleConnect, this,/*shared_from_this(),*/
                    boost::asio::placeholders::error));
}

void ActiveTcpConnection::handleConnect(const boost::system::error_code& error)
{
    if (!error) {
        _utils.wirteLog(GLUtils::LL_INFO,
                "Connect to %1%(%2%:%3%): success", this->id(), _serverIp,
                _serverPort);
        this->startReceive();

    } else {
        _utils.wirteLog(GLUtils::LL_ERROR,
                "Connect to %1%(%2%:%3%): %4%", this->id(), _serverIp, _serverPort,
                error.message());
    }

}

} } // GreenLeaf::GLNetIO

