/*
 * Sessions.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
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
    ConnectionsPtrMap _connectionsPtrMap;

};
typedef boost::shared_ptr<Sessions> SessionsPtr;

} } // GreenLeaf::GLNetIO

#endif // SESSIONS_H

