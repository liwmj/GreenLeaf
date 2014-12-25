/*
 * GLNetIO.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
 */

#include <iostream>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/GLUtils.h"

#include "GreenLeaf/GLNetIO/SessionManager.h"
#include "GreenLeaf/GLNetIO/TcpAcceptor.h"
#include "GreenLeaf/GLNetIO.h"

namespace GreenLeaf {
namespace GLNetIO {

NetIO& NetIO::instance()
{
    static NetIO _gInstance;
    return _gInstance;
}

NetIO::NetIO(): _acceptor()
{
}

NetIO::~NetIO()
{
}

void NetIO::tcpAcceptor(const unsigned short& port,
        boost::function<void(boost::shared_ptr<TcpConnection>)> operation)
{
    _acceptor.reset(new TcpAcceptor(GLUtils::Utils::instance().ioService(), port, operation));
}

TcpConnectionPtr NetIO::connection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType)
{
    return SessionManager::instance().connection(userID, sessionID, connectionType);
}

void NetIO::addConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    return SessionManager::instance().addConnection(userID, sessionID, connectionType, conn);
}

void NetIO::removeConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType)
{
    return SessionManager::instance().removeConnection(userID, sessionID, connectionType);
}

void NetIO::modifyConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    return SessionManager::instance().modifyConnection(userID, sessionID, connectionType, conn);
}

const std::string NetIO::connectionNumber()
{
    return SessionManager::instance().connectionNumber();
}

const std::string NetIO::singalUserConnectionNumber(const std::string& userID)
{
    return SessionManager::instance().singalUserConnectionNumber(userID);
}

} } // GreenLeaf::GLNetIO

