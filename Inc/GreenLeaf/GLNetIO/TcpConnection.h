/**
 * @file TcpConnection.h
 * @brief tcp连接的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "GreenLeaf/GLNetIO/MessageProtocol.h"

namespace GreenLeaf {
namespace GLNetIO {

class MessageBuffer;
class ParseRequestData;
class BundleResponseData;

/**
 * @brief tcp基础连接类
 */
class TcpConnection: public boost::enable_shared_from_this<TcpConnection>
{
public:
    typedef boost::asio::ip::tcp tcp;

    explicit TcpConnection(boost::asio::io_service& service, const std::string& id);
    virtual ~TcpConnection();

    void setConnectionProps(const std::string& userID,
            const std::string& sessionType,
            const std::string& connectionType);
    const std::string& userID() const;
    const std::string& sessionType() const;
    const std::string& connectionType() const;

    tcp::socket& socket();
    const std::string& id() const;

    void setRemoveCallBack(boost::function<void(const std::string&,
            const std::string&,
            const std::string&)> operation =
                    boost::function<void(const std::string&,
                            const std::string&,
                            const std::string&)>());

    void startReceive();
    void sendMessage(std::string msg);
    void sendBundleMessage(ResponseBufferPtr data);

    void handleTimeout();

protected:
    void handleSend(const boost::system::error_code& error);
    void handleReceive(const boost::system::error_code& error,
            size_t bytes,
            boost::shared_ptr<MessageBuffer> msg);
    void handleData(MessageBufferPtr msg, const std::size_t& bytes);

private:
    std::string _userID;                            /**< 用户的唯一标示 */
    std::string _sessionType;                       /**< session类型 */
    std::string _connectionType;                    /**< 连接类型 */
    std::string _id;                                /**< 连接ID */
    tcp::socket _sock;                              /**< 连接里的sock */
    std::time_t _lastRecvTime;                      /**< 最后一次接受时间 */
    boost::asio::io_service& _netIOService;         /**< 通讯所需io */
    boost::asio::deadline_timer _netTimer;          /**< 连接定时检查器 */

    boost::shared_ptr<ParseRequestData> _request;   /**< 请求缓冲区 */

    boost::function<void(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType)> _operationRemoveConnection;

};
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

} } // GreenLeaf::GLNetIO

#endif // TCPCONNECTION_H

