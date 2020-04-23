/**
 * @file TcpConnection.cpp
 * @brief Tcp连接的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "GreenLeaf/GLUtils.h"

#include "GreenLeaf/GLNetIO/MsgHandlerRepository.h"
#include "GreenLeaf/GLNetIO/ParseRequestData.h"
#include "GreenLeaf/GLNetIO/BundleResponseData.h"
#include "GreenLeaf/GLNetIO/TcpConnection.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 初始化TcpConnection对象
 * @param service 运行所需io
 * @param id 连接id
 */
TcpConnection::TcpConnection(boost::asio::io_service& service, const std::string& id):
        _id(id),
        _sock(service),
        _lastRecvTime(std::time(0)),
        _netIOService(GLUtils::Utils::instance().ioService()),
        _netTimer(_netIOService),
        _request(new ParseRequestData)
{
}

/**
 * @brief 析构TcpConnection对象
 */
TcpConnection::~TcpConnection()
{
}

/**
 * @brief 设置连接的属性
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 */
void TcpConnection::setConnectionProps(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType)
{
    _userID = userID;
    _sessionType = sessionType;
    _connectionType = connectionType;
}

/**
 * @brief 获取用户的唯一标示
 * @return 返回用户的唯一标示
 */
const std::string& TcpConnection::userID() const
{
    return _userID;
}

/**
 * @brief 获取连接的session类型
 * @return 返回连接的session类型
 */
const std::string& TcpConnection::sessionType() const
{
    return _sessionType;
}

/**
 * @brief 获取连接的连接类型
 * @return 返回连接的连接类型
 */
const std::string& TcpConnection::connectionType() const
{
    return _connectionType;
}

/**
 * @brief 获取当前连接的socket
 * @return 返回单签连接的socket
 */
TcpConnection::tcp::socket& TcpConnection::socket()
{
    return _sock;
}

/**
 * @brief 获取连接id
 * @return 返回连接id
 */
const std::string& TcpConnection::id() const
{
    return _id;
}

/**
 * @brief 设置删除连接所需的回调
 * @param operation 指定回调
 */
void TcpConnection::setRemoveCallBack(boost::function<void(const std::string&,
        const std::string&,
        const std::string&)> operation)
{
    _operationRemoveConnection = operation;
}

/**
 * @brief 开始接受数据
 */
void TcpConnection::startReceive()
{
    MessageBufferPtr msg(new MessageBuffer);

    boost::asio::async_read(
            _sock,
            boost::asio::buffer(msg->_data, BS_BUFFERSIZE),
            boost::asio::transfer_at_least(1),
            boost::bind(&TcpConnection::handleReceive, shared_from_this(),
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred,
                    msg));
}

/**
 * @brief 发送数据
 * @param msg 指定数据
 */
void TcpConnection::sendMessage(std::string msg)
{
    boost::asio::async_write(
            _sock,
            boost::asio::buffer(msg),
            boost::bind(&TcpConnection::handleSend, shared_from_this(),
                    boost::asio::placeholders::error));
}

/**
 * @brief 发送打包好的应答数据
 * @param data 应答数据的指针
 */
void TcpConnection::sendBundleMessage(ResponseBufferPtr data)
{
    BundleResponseData response;

    boost::asio::async_write(
                _sock,
                boost::asio::buffer(response.bundleAllData(data)),
                boost::bind(&TcpConnection::handleSend, shared_from_this(),
                        boost::asio::placeholders::error));

}

/**
 * @brief 连接超时检查
 */
void TcpConnection::handleTimeout()
{
    if (!_sock.is_open())
        return ;

    std::time_t maxTimeout = 2 * 60;
    std::time_t now = std::time(0);
    std::time_t interval = now - _lastRecvTime;
    if (interval >= maxTimeout) {
        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin);

        if (!_operationRemoveConnection.empty())
            _operationRemoveConnection(_userID, _sessionType, _connectionType);

        return ;
    }

    _netTimer.expires_from_now(boost::posix_time::seconds(maxTimeout));
    _netTimer.async_wait(boost::bind(&TcpConnection::handleTimeout, shared_from_this()));
}

/**
 * @brief 处理发送
 * @param error 错误代码
 */
void TcpConnection::handleSend(const boost::system::error_code& error)
{
    if (error) {
        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin);


        if (!_operationRemoveConnection.empty())
            _operationRemoveConnection(_userID, _sessionType, _connectionType);
    }
}

/**
 * @brief 处理接受
 * @param error 错误代码
 * @param bytes 接受到的数据大小
 * @param msg 接受到的数据
 */
void TcpConnection::handleReceive(const boost::system::error_code& error,
        std::size_t bytes,
        MessageBufferPtr msg)
{
    if (!error) {
        if (!_sock.is_open())
            return ;

        this->handleData(msg, bytes);

        msg.reset(new MessageBuffer);
        boost::asio::async_read(
                _sock,
                boost::asio::buffer(msg->_data),
                boost::asio::transfer_at_least(1),
                boost::bind(&TcpConnection::handleReceive, shared_from_this(),
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred,
                        msg));

    } else {
        boost::system::error_code ec;
        _sock.close(ec);
        _netTimer.cancel(ec);
        _netTimer.expires_at(boost::posix_time::pos_infin);


        if (!_operationRemoveConnection.empty())
            _operationRemoveConnection(_userID, _sessionType, _connectionType);
    }
}

/**
 * @brief 处理接受到的数据
 * @param msg 需处理的数据
 * @param bytes 数据大小
 */
void TcpConnection::handleData(MessageBufferPtr msg, const std::size_t& bytes)
{
    msg->_data[bytes] = '\0';
    _lastRecvTime = std::time(0);

    _request->parseAllData(msg->_data, bytes);

    if (_request->_requestBuffer->_reqStatus == REQ_DONE ||
            _request->_requestBuffer->_reqStatus == REQ_ERROR) {
        RequestHandler handler =
                MsgHandlerRepository<RequestHandler>::instance().handler(
                        _request->_requestBuffer->_methon);

        if (!handler.empty()) {
            _request->_requestBuffer->_conn = shared_from_this();
            _sock.get_io_service().post(boost::bind(handler, _request->_requestBuffer));
        }

        _request.reset(new ParseRequestData);

    }
}

} } // GreenLeaf::GLNetIO

