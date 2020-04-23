/*
 * UserManagers.h
 *
 *  Created on: Nov 12, 2014
 *      Author: Mason
 */

#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/noncopyable.hpp>
#include <boost/bind.hpp>

#include "GreenLeaf/GLNetIO.h"
#include "GreenLeaf/GLDBIO.h"

#include "GreenLeaf/MsgServer/DataCacheManager.h"

namespace GreenLeaf {
namespace Server {

class UserManager: private boost::noncopyable
{
public:
    static UserManager& instance();

    GLNetIO::TcpConnectionPtr connection(const std::string& loginName,
            const std::string& sessionType,
            const std::string& connectionType);
    void addConnection(const std::string& loginName,
            const std::string& sessionType,
            const std::string& connectionType,
            const GLNetIO::TcpConnectionPtr conn);
    void removeConnection(const std::string& loginName,
            const std::string& sessionType,
            const std::string& connectionType);
    void modifyConnection(const std::string& loginName,
            const std::string& sessionType,
            const std::string& connectionType,
            const GLNetIO::TcpConnectionPtr conn);

    const std::string dataCacheNumber();

    DataCachePtr dataCache(const std::string& loginName);
    void setDataCache(const std::string& loginName, DataCachePtr dataCache);


private:
    explicit UserManager();

private:
    GLNetIO::NetIO& _netIO;
    GLDBIO::DBIO& _dbIO;
    DataCacheManager& _dataCacheManager;

    boost::mutex _mutex;

};

} } // GreenLeaf::Server

#endif // USERMANAGER_H

