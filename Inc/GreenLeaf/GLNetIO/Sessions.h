/**
 * @file Sessions.h
 * @brief session集合的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef SESSIONS_H
#define SESSIONS_H

#include <map>
#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/GLNetIO.h"
#include "GreenLeaf/GLNetIO/Connections.h"

namespace GreenLeaf {
namespace GLNetIO {

typedef std::map<std::string, ConnectionsPtr> ConnectionsPtrMap;

/**
 * @brief session集合类
 */
class Sessions
{
public:
    const ConnectionsPtrMap& connectionsPtrMap() const;

    ConnectionsPtr session(const std::string sessionType);
    void addSession(const std::string sessionType,
            ConnectionsPtr connections);
    void removeSession(const std::string sessionType);
    void modifySession(const std::string sessionType,
            ConnectionsPtr connections);

private:
    ConnectionsPtrMap _connectionsPtrMap;   /**< 存放连接集合的容器 */

};
typedef boost::shared_ptr<Sessions> SessionsPtr;

} } // GreenLeaf::GLNetIO

#endif // SESSIONS_H

