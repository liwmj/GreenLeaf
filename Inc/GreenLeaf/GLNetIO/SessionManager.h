/*
 * SessionManager.h
 *
 *  Created on: Dec 15, 2014
 *      Author: wim
 */

#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include "GreenLeaf/GLNetIO/Sessions.h"
#include "GreenLeaf/GLNetIO/Connections.h"

namespace GreenLeaf {
namespace GLNetIO {

class SessionManager: private boost::noncopyable
{
public:
    static SessionManager& instance();

    ConnectionsPtr session(const std::string& userID,
            const std::string& sessionType);
    void addSession(const std::string& userID,
            const std::string& sessionType,
            const ConnectionsPtr connections);
    void removeSession(const std::string& userID,
            const std::string& sessionType);
    void modifySession(const std::string& userID,
            const std::string& sessionType,
            const ConnectionsPtr connections);

    TcpConnectionPtr connection(const std::string& userID,
            const std::string& sessionType,
            const std::string& connectionType);
    void addConnection(const std::string& userID,
            const std::string& sessionType,
            const std::string& connectionType,
            const TcpConnectionPtr conn);
    void removeConnection(const std::string& userID,
            const std::string& sessionType,
            const std::string& connectionType);
    void modifyConnection(const std::string& userID,
            const std::string& sessionType,
            const std::string& connectionType,
            const TcpConnectionPtr conn);

    const std::string connectionNumber();
    const std::string singalUserConnectionNumber(const std::string& userID);

private:
    typedef std::map<std::string, SessionsPtr> SessionsPtrMap;

    SessionsPtrMap _sessionsPtrMap;
    boost::mutex _mutex;

};

} } // GreenLeaf::GLNetIO

#endif // SESSIONMANAGER_H

