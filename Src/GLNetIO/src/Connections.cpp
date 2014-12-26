/**
 * @file Connections.cpp
 * @brief 连接集合的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <string>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/Connections.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 获取连接集合
 * @return 返回连接集合
 */
const TcpConnectionPtrMap& Connections::tcpConnectionPtrMap() const
{
    return _tcpConnectionPtrMap;
}

/**
 * @brief 获取一条连接
 * @param connectionType 连接类型
 * @return 返回连接的指针
 */
TcpConnectionPtr Connections::connection(const std::string connectionType)
{
    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.find(connectionType);
    return it == _tcpConnectionPtrMap.end() ? TcpConnectionPtr() : it->second;
}

/**
 * @brief 添加一条连接
 * @param connectionType 连接类型
 * @param conn 指定连接
 */
void Connections::addConnection(const std::string connectionType,
        TcpConnectionPtr conn)
{
    if (!conn.get())
        return ;

    _tcpConnectionPtrMap.insert(std::make_pair(connectionType, conn));
    conn->setRemoveCallBack(boost::bind(&Connections::removeCheckConnection, shared_from_this(), conn));
}

/**
 * @brief 删除一条连接
 * @param connectionType 连接类型
 */
void Connections::removeConnection(const std::string connectionType)
{
    _tcpConnectionPtrMap.erase(connectionType);
}

/**
 * @brief 检查后删除连接
 * @param connection 指定连接
 */
void Connections::removeCheckConnection(TcpConnectionPtr connection)
{
    if (!connection.get())
        return ;

    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.begin();
    for (; it != _tcpConnectionPtrMap.end(); ++it) {
        if (it->second.get()) {
            if (it->second->id() == connection->id()) {
                _tcpConnectionPtrMap.erase(it->first);

            }
        }
    }
}

/**
 * @brief 更改一条连接
 * @param connectionType 连接类型
 * @param conn 指定连接
 */
void Connections::modifyConnection(const std::string connectionType,
        TcpConnectionPtr conn)
{
    if (!conn.get())
        return ;

    TcpConnectionPtrMap::iterator it = _tcpConnectionPtrMap.find(connectionType);
    if (it != _tcpConnectionPtrMap.end()) {
        it->second.reset();
        it->second = conn;
    }
}

} } //GreenLeaf::GLNetIO

