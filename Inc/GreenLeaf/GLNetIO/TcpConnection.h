/*
 * Connection.h
 *
 *  Created on: Nov 5, 2014
 *      Author: wim
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
    std::string _userID;
    std::string _sessionType;
    std::string _connectionType;
    std::string _id;
    tcp::socket _sock;
    std::time_t _lastRecvTime;
    boost::asio::io_service& _netIOService;
    boost::asio::deadline_timer _netTimer;

    boost::shared_ptr<ParseRequestData> _request;

    boost::function<void(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType)> _operationRemoveConnection;

};
typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

} } // GreenLeaf::GLNetIO

#endif // TCPCONNECTION_H

