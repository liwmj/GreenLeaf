/*
 * TcpAcceptor.h
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
 */

#ifndef TCPACCEPTOR_H
#define TCPACCEPTOR_H

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>

#include "GreenLeaf/GLUtils.h"

namespace GreenLeaf {
namespace GLNetIO {

class TcpConnection;

class TcpAcceptor
{
public:
    typedef boost::asio::ip::tcp tcp;

    explicit TcpAcceptor(boost::asio::io_service& service,
            unsigned short listenPort,
            boost::function<void(boost::shared_ptr<TcpConnection>)> operation =
                    boost::function<void(boost::shared_ptr<TcpConnection>)>());

private:
    void handleAccept(boost::shared_ptr<TcpConnection> conn,
            const boost::system::error_code& error);

private:
    GLUtils::Utils& _utils;
    boost::asio::io_service& _svc;
    tcp::acceptor _acceptor;
    boost::uuids::random_generator _rgen;

    boost::function<void(boost::shared_ptr<TcpConnection> conn)> _operationAfterAccept;
};


} } // GreenLeaf::GLNetIO

#endif // ACCEPTOR_H

