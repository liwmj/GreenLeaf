/**
 * @file SessionManager.cpp
 * @brief session管理的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/format.hpp>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/SessionManager.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 创建SessionManager的单例对象
 * @return 返回SessionManager对象
 */
SessionManager& SessionManager::instance()
{
    static SessionManager _gInstance;
    return _gInstance;
}

/**
 * @brief 获取一个session
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @return session的指针
 */
ConnectionsPtr SessionManager::session(const std::string& userID,
        const std::string& sessionType)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        return it->second->session(sessionType);
    } else {
        return ConnectionsPtr();
    }
}

/**
 * @brief 添加一个sessionn
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connections 连接集合
 */
void SessionManager::addSession(const std::string& userID,
        const std::string& sessionType,
        const ConnectionsPtr connections)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        it->second->removeSession(sessionType);
        it->second->addSession(sessionType, connections);
    } else {
        it->second->addSession(sessionType, connections);
    }
}

/**
 * @brief 删除一个session
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 */
void SessionManager::removeSession(const std::string& userID,
        const std::string& sessionType)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        it->second->removeSession(sessionType);
    }
}

/**
 * @brief 更改一个session
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connections 连接集合
 */
void SessionManager::modifySession(const std::string& userID,
        const std::string& sessionType,
        const ConnectionsPtr connections)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        it->second->modifySession(sessionType, connections);
    }
}

/**
 * @brief 获取一个连接
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 * @return 返回连接的指针
 */
TcpConnectionPtr SessionManager::connection(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        if (it->second->session(sessionType)) {
            return it->second->session(sessionType)->connection(connectionType);
        } else {
            return GLNetIO::TcpConnectionPtr();
        }
    } else {
        return GLNetIO::TcpConnectionPtr();
    }
}

/**
 * @brief 添加一个连接
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 * @param conn 指定连接
 */
void SessionManager::addConnection(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    boost::mutex::scoped_lock lock(_mutex);
    ConnectionsPtr connectionsPtr(new Connections);

    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        if (it->second->session(sessionType)) {
            if (it->second->session(sessionType)->connection(connectionType)) {
                it->second->session(sessionType)->modifyConnection(connectionType, conn);
                conn->setConnectionProps(userID, sessionType, connectionType);
                conn->setRemoveCallBack(boost::bind(&SessionManager::removeConnection,
                        this, _1, _2, _3));

            } else {
                it->second->session(sessionType)->addConnection(connectionType, conn);
                conn->setConnectionProps(userID, sessionType, connectionType);
                conn->setRemoveCallBack(boost::bind(&SessionManager::removeConnection,
                        this, _1, _2, _3));
            }

        } else {
            connectionsPtr->addConnection(connectionType, conn);
            conn->setConnectionProps(userID, sessionType, connectionType);
            conn->setRemoveCallBack(boost::bind(&SessionManager::removeConnection,
                    this, _1, _2, _3));
            it->second->addSession(sessionType, connectionsPtr);
        }

    } else {
        SessionsPtr sessionsPtr(new Sessions);
        connectionsPtr->addConnection(connectionType, conn);
        conn->setConnectionProps(userID, sessionType, connectionType);
        conn->setRemoveCallBack(boost::bind(&SessionManager::removeConnection,
                this, _1, _2, _3));
        sessionsPtr->addSession(sessionType, connectionsPtr);
        _sessionsPtrMap.insert(std::make_pair(userID, sessionsPtr));
    }
}

/**
 * @brief 删除一个连接
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 */
void SessionManager::removeConnection(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        if (it->second->session(sessionType)) {
            if (it->second->session(sessionType)->connection(connectionType)) {
                it->second->session(sessionType)->removeConnection(connectionType);

                if (!it->second->session(sessionType)->tcpConnectionPtrMap().size())
                    it->second->removeSession(sessionType);
            }
        }
    }
}

/**
 * @brief 更改一个连接
 * @param userID 用户的唯一标示
 * @param sessionType session类型
 * @param connectionType 连接类型
 * @param conn 指定连接
 */
void SessionManager::modifyConnection(const std::string& userID,
        const std::string& sessionType,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        if (it->second->session(sessionType)) {
            if (it->second->session(sessionType)->connection(connectionType)) {
                it->second->session(sessionType)->modifyConnection(connectionType, conn);
                conn->setConnectionProps(userID, sessionType, connectionType);
            }
        }
    }
}

/**
 * @brief 获取连接数
 * @return 返回连接数
 */
const std::string SessionManager::connectionNumber()
{
    boost::mutex::scoped_lock lock(_mutex);
    std::size_t connectionNumber = 0;

    SessionsPtrMap::iterator it = _sessionsPtrMap.begin();

    for (; it != _sessionsPtrMap.end(); ++it) {
        ConnectionsPtrMap connectionsPtr = it->second->connectionsPtrMap();
        ConnectionsPtrMap::iterator iter = connectionsPtr.begin();

        for (; iter != connectionsPtr.end(); ++iter) {
            connectionNumber += iter->second->tcpConnectionPtrMap().size();
        }
    }

    return boost::str(boost::format("%d") % connectionNumber);
}

/**
 * @brief 获取单个用户的连接数
 * @param userID 用户的唯一标示
 * @return 返回单个用户的连接数
 */
const std::string SessionManager::singalUserConnectionNumber(const std::string& userID)
{
    boost::mutex::scoped_lock lock(_mutex);
    std::size_t connectionNumber = 0;

    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);

    if (it != _sessionsPtrMap.end()) {
        ConnectionsPtrMap connectionsPtr = it->second->connectionsPtrMap();
        ConnectionsPtrMap::iterator iter = connectionsPtr.begin();

        for (; iter != connectionsPtr.end(); ++iter) {
            connectionNumber += iter->second->tcpConnectionPtrMap().size();
        }
    }

    return boost::str(boost::format("%d") % connectionNumber);
}

} } // GreenLeaf::GLNetIO

