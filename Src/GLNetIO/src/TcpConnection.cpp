/*
 * Connection.cpp
 *
 *  Created on: Nov 5, 2014
 *      Author: wim
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

TcpConnection::TcpConnection(boost::asio::io_service& service, const std::string& id):
        _id(id),
        _sock(service),
        _lastRecvTime(std::time(0)),
        _netIOService(GLUtils::Utils::instance().ioService()),
        _netTimer(_netIOService),
        _request(new ParseRequestData)
{
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::setConnectionProps(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType)
{
    _userID = userID;
    _sessionType = sessionType;
    _connectionType = connectionType;
}

const std::string& TcpConnection::userID() const
{
    return _userID;
}

const std::string& TcpConnection::sessionType() const
{
    return _sessionType;
}

const std::string& TcpConnection::connectionType() const
{
    return _connectionType;
}

TcpConnection::tcp::socket& TcpConnection::socket()
{
    return _sock;
}
const std::string& TcpConnection::id() const
{
    return _id;
}

void TcpConnection::setRemoveCallBack(boost::function<void(const std::string&,
        const std::string&,
        const std::string&)> operation)
{
    _operationRemoveConnection = operation;
}

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

void TcpConnection::sendMessage(std::string msg)
{
    boost::asio::async_write(
            _sock,
            boost::asio::buffer(msg),
            boost::bind(&TcpConnection::handleSend, shared_from_this(),
                    boost::asio::placeholders::error));
}

void TcpConnection::sendBundleMessage(ResponseBufferPtr data)
{
    BundleResponseData response;
//    std::cout << "BUNDLE_DATA:-----------------------\n" << response.bundleAllData(data) << "--------------------------\n" << std::endl;

    boost::asio::async_write(
                _sock,
                boost::asio::buffer(response.bundleAllData(data)),
                boost::bind(&TcpConnection::handleSend, shared_from_this(),
                        boost::asio::placeholders::error));

}

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

void TcpConnection::handleReceive(const boost::system::error_code& error,
        std::size_t bytes,
        MessageBufferPtr msg)
{
    if (!error) {
        if (!_sock.is_open())
            return ;

//        std::cout << "DATA:-----------------------\n" << std::string(msg->_data) << "\n--------------------------\n" << std::endl;
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

