/*
 * TcpAcceptor.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
 */

#include <iostream>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/TcpConnection.h"
#include "GreenLeaf/GLNetIO/TcpAcceptor.h"

namespace GreenLeaf {
namespace GLNetIO {

TcpAcceptor::TcpAcceptor(boost::asio::io_service& service, unsigned short listenPort,
        boost::function<void(TcpConnectionPtr)> operation):
                _utils(GLUtils::Utils::instance()),
                _svc(service),
                _acceptor(_svc, tcp::endpoint(tcp::v4(), listenPort)),
                _operationAfterAccept(operation)
{
    TcpConnectionPtr conn(new TcpConnection(_svc, _utils.randUuidToString()));

    _acceptor.async_accept(conn->socket(),
            boost::bind(&TcpAcceptor::handleAccept, this, conn,
                    boost::asio::placeholders::error));
}

void TcpAcceptor::handleAccept(TcpConnectionPtr conn,
        const boost::system::error_code& error)
{
    if (!error) {
        if (!_operationAfterAccept.empty())
            _operationAfterAccept(conn);

        conn->startReceive();
        conn->handleTimeout();

        boost::system::error_code ec;
        boost::asio::ip::tcp::endpoint remote =
                conn->socket().remote_endpoint(ec);
    }

    TcpConnectionPtr connection(new TcpConnection(_svc, _utils.randUuidToString()));

    _acceptor.async_accept(connection->socket(),
            boost::bind(&TcpAcceptor::handleAccept, this, connection,
                    boost::asio::placeholders::error));
}

} } // GreenLeaf::GLNetIO

