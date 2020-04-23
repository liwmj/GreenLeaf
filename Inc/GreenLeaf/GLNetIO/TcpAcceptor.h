/**
 * @file TcpAcceptor.h
 * @brief tcp监听的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
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

/**
 * @brief tcp监听类
 */
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
    GLUtils::Utils& _utils;                 /**< GLUtils库的引用 */
    boost::asio::io_service& _svc;          /**< 监听需要使用的io */
    tcp::acceptor _acceptor;                /**< 监听对象 */

    boost::function<void(boost::shared_ptr<TcpConnection> conn)> _operationAfterAccept;
};


} } // GreenLeaf::GLNetIO

#endif // ACCEPTOR_H

