/*
 * UserManagers.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: Mason
 */

#include "GreenLeaf/MsgServer/UserManager.h"

namespace GreenLeaf {
namespace Server {

UserManager& UserManager::instance()
{
    static UserManager _gInstance;
    return _gInstance;
}

UserManager::UserManager():
        _netIO(GLNetIO::NetIO::instance()),
        _dbIO(GLDBIO::DBIO::instance()),
        _dataCacheManager(DataCacheManager::instance())
{
}

GLNetIO::TcpConnectionPtr UserManager::connection(const std::string& loginName,
        const std::string& sessionType,
        const std::string& connectionType)
{
    return _netIO.connection(loginName, sessionType, connectionType);
}

void UserManager::addConnection(const std::string& loginName,
        const std::string& sessionType,
        const std::string& connectionType,
        const GLNetIO::TcpConnectionPtr conn)
{
    _netIO.addConnection(loginName, sessionType, connectionType, conn);
}

void UserManager::removeConnection(const std::string& loginName,
        const std::string& sessionType,
        const std::string& connectionType)
{
    _netIO.removeConnection(loginName, sessionType, connectionType);
}

void UserManager::modifyConnection(const std::string& loginName,
        const std::string& sessionType,
        const std::string& connectionType,
        const GLNetIO::TcpConnectionPtr conn)
{
    _netIO.modifyConnection(loginName, sessionType, connectionType, conn);
}

const std::string UserManager::dataCacheNumber()
{
    return _dataCacheManager.dataCacheNumber();
}

DataCachePtr UserManager::dataCache(const std::string& loginName)
{
    return _dataCacheManager.dataCache(loginName);
}

void UserManager::setDataCache(const std::string& loginName, DataCachePtr dataCache)
{
    _dataCacheManager.setDataCache(loginName, dataCache);
}

} } // GreenLeaf::Server

