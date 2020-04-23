/**
 * @file SessionManager.h
 * @brief session管理的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

#include "GreenLeaf/GLNetIO/Sessions.h"
#include "GreenLeaf/GLNetIO/Connections.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief session管理类
 */
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

    SessionsPtrMap _sessionsPtrMap;     /**< 存放session的容器 */
    boost::mutex _mutex;                /**< session管理所需的锁 */

};

} } // GreenLeaf::GLNetIO

#endif // SESSIONMANAGER_H

