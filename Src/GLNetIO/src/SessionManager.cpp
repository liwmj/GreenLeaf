/*
 * SessionManager.cpp
 *
 *  Created on: Dec 15, 2014
 *      Author: wim
 */

#include <boost/format.hpp>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO/SessionManager.h"

namespace GreenLeaf {
namespace GLNetIO {

SessionManager& SessionManager::instance()
{
    static SessionManager _gInstance;
    return _gInstance;
}

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

void SessionManager::removeSession(const std::string& userID,
        const std::string& sessionType)
{
    boost::mutex::scoped_lock lock(_mutex);
    SessionsPtrMap::iterator it = _sessionsPtrMap.find(userID);
    if (it != _sessionsPtrMap.end()) {
        it->second->removeSession(sessionType);
    }
}

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

