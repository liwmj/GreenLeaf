/**
 * @file ActiveTcpConnection.cpp
 * @brief 主动连接的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/ActiveTcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

    /**
     * @brief 初始化ActiveTcpConnection对象
     * @param service 指定操作io
     * @param id 连接的id
     * @param ip 地址
     * @param port 端口):
     */
ActiveTcpConnection::ActiveTcpConnection(boost::asio::io_service& service,
        const std::string& id, const std::string& ip, unsigned short port):
                _utils(GLUtils::Utils::instance()),
                TcpConnection(service, id), _serverIp(ip), _serverPort(port)
{
}

/**
 * @brief 主动请求连接
 */
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

/**
 * @brief 处理请求成功后的处理
 * @param error 错误码
 */
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

