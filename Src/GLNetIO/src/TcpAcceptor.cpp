/**
 * @file TcpAcceptor.cpp
 * @brief 监听TCP的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/TcpConnection.h"
#include "GreenLeaf/GLNetIO/TcpAcceptor.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 初始化TcpAcceptor对象
 * @param service 运行所需io
 * @param listenPort 监听端口
 * @param operation 回调函数
 */
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

/**
 * @brief 处理监听成功
 * @param conn 监听到的连接
 * @param error 错误代码
 */
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

