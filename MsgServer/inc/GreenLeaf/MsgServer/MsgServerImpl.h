/*
 * DemoServerImpl.h
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
 */

#ifndef DEMOSERVERIMPL_H
#define DEMOSERVERIMPL_H

#include <fstream>

#include "GreenLeaf/GLUtils.h"
#include "GreenLeaf/GLDiskIO.h"
#include "GreenLeaf/GLNetIO.h"
#include "GreenLeaf/GLDBIO.h"

#include "GreenLeaf/MsgServer/HandlerManager.h"
#include "GreenLeaf/MsgServer/UserManager.h"

namespace GreenLeaf {
namespace Server {

class MsgServerImpl
{
public:
    explicit MsgServerImpl();

    void run();
    void stop();

private:
    const bool initConfigs();
    const bool initLogger();
    const bool initDbConnection();
    void initServer();

private:
    GLUtils::Utils& _utils;
    GLDiskIO::DiskIO& _diskIO;
    GLNetIO::NetIO& _netIO;
    GLDBIO::DBIO& _dbIO;
    HandlerManager& _handlerManager;
    UserManager& _userManger;

    struct ServerConfigData {
        ServerConfigData(): _serverPort(6660), _threadNUm(0), _logLevel(1),
                _dbConnPoolSize(100) {}

        unsigned short _serverPort;
        std::size_t _threadNUm;
        std::size_t _logLevel;

        std::string _dbServerip;
        std::string _dbUsername;
        std::string _dbPasswd;
        std::string _dbName;
        std::size_t _dbConnPoolSize;

    };
    ServerConfigData _configData;

    std::fstream _fout;

};

} } // GreenLeaf::Server

#endif // DEMOSERVERIMPL_H

