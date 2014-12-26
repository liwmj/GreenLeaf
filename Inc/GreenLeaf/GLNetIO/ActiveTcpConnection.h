/**
 * @file ActiveTcpConnection.h
 * @brief 主动连接的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef ACTIVETCPCONNECTION_H
#define ACTIVETCPCONNECTION_H

#include "GreenLeaf/GLUtils.h"

#include "GreenLeaf/GLNetIO/TcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 主动连接类
 */
class ActiveTcpConnection: public TcpConnection
{
public:
    ActiveTcpConnection(boost::asio::io_service& service, const std::string& id,
            const std::string& serverIp, unsigned short serverPort);

    void connect();

private:
    void handleConnect(const boost::system::error_code& error);

private:
    GLUtils::Utils& _utils;         /**< GLUtils库的引用 */
    const std::string _serverIp;    /**< 服务器地址 */
    unsigned short _serverPort;     /**< 服务器端口 */

};
typedef boost::shared_ptr<ActiveTcpConnection> ActiveTcpConnectionPtr;

} } // GreenLeaf::GLNetIO

#endif // ACTIVETCPCONNECTION_H

