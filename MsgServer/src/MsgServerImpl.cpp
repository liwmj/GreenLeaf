/*
 * ServerImpl.cpp
 *
 *  Created on: Nov 4, 2014
 *      Author: wim
 */

#include <csignal>
#include <string>
#include <vector>
#include <iostream>
#include <boost/thread.hpp>

#include "GreenLeaf/MsgServer/MsgServerImpl.h"

namespace {

using namespace GreenLeaf;

void quitFunc(int sig)
{
    GLUtils::Utils::instance().wirteLog(GLUtils::LL_DEBUG, "Caught signal SIGTERM");
    GLUtils::Utils::instance().stop();
}

}

namespace GreenLeaf {
namespace Server {

MsgServerImpl::MsgServerImpl():
        _utils(GLUtils::Utils::instance()),
        _diskIO(GLDiskIO::DiskIO::instance()),
        _netIO(GLNetIO::NetIO::instance()),
        _dbIO(GLDBIO::DBIO::instance()),
        _handlerManager(HandlerManager::instance()),
        _userManger(UserManager::instance()),
        _configData(ServerConfigData())
{
}

void MsgServerImpl::run()
{
    std::cout << "InitConfigs loading...." << std::endl;
    if (!this->initConfigs()) {
        std::cout << "initConfigs error" << std::endl;
        return;
    }

    std::cout << "InitLogger loading...." << std::endl;
    if (!this->initLogger()) {
        std::cout << "initLogger error" << std::endl;
        return;
    }

    std::cout << "InitDbConnection loading...." << std::endl;
    if (!this->initDbConnection()) {
        std::cout << "initDbConnection error" << std::endl;
        return ;
    }

    try {
        std::cout << "InitServer loading...." << std::endl;
        this->initServer();

    } catch (std::exception& e) {
        _utils.wirteLog(
                GLUtils::LL_ERROR,
                "Caught an exception when launching the server process: %1%",
                e.what());

    } catch (...) {
        _utils.wirteLog(
                GLUtils::LL_ERROR,
                "Caught an exception when launching the server process: %1%");
    }
}

void MsgServerImpl::stop()
{
    _utils.stop();
}

const bool MsgServerImpl::initConfigs()
{
    std::string filePath(_utils.currentPath());
    filePath += "/conf/MsgServer.conf";

    if (!_diskIO.loadIniFile(filePath)) {
        return false;
    } else {
        _configData._serverPort = _diskIO.iniData<unsigned short>("Server.Port", 6660);
        _configData._threadNUm = _diskIO.iniData<std::size_t>("Server.ThreadNumber", 0);
        _configData._logLevel = _diskIO.iniData<std::size_t>("Server.LogLevel", 1);
        _configData._dbServerip = _diskIO.iniData<std::string>("DB.ServerIP", "127.0.0.1");
        _configData._dbUsername = _diskIO.iniData<std::string>("DB.Username", "");
        _configData._dbPasswd = _diskIO.iniData<std::string>("DB.Passwd", "");
        _configData._dbName = _diskIO.iniData<std::string>("DB.Name", "");
        _configData._dbConnPoolSize = _diskIO.iniData<std::size_t>("DB.ConnectionPoolSize", 100);
    }
    return true;
}

const bool MsgServerImpl::initLogger()
{
    std::vector<std::string> datatime(_utils.splitString(_utils.localDatatimeF(), "-"));
    std::string path(_utils.currentPath());
    path += "/log";
    for (int i = 0; i < datatime.size(); ++i) {
        path += "/"; path += datatime.at(i);
    }

    _utils.createPaths(path);
    std::string fileName(path);
    fileName += "/"; fileName += _utils.localDatatimeFT(); fileName += ".txt";

    _fout.open(fileName.c_str(), std::ios::out | std::ios::app);

    if (!_fout) {
        return false;
    }

    _utils.initLogger(GLUtils::LoggerLevel(_configData._logLevel), &_fout);
    _utils.wirteLog(GLUtils::LL_DEBUG, "Message Server starting ...");

    return true;
}

const bool MsgServerImpl::initDbConnection()
{
    if (!_dbIO.initMySqlConnectionPool(_configData._dbServerip,
            _configData._dbUsername,
            _configData._dbPasswd,
            _configData._dbName,
            _configData._dbConnPoolSize)) {
        return false;
    }

    return true;
}

void MsgServerImpl::initServer()
{
    if (!_handlerManager.registerAllHandlers()) {
        _utils.wirteLog(GLUtils::LL_ERROR, "Register Handlers error");
        return ;
    }

    _utils.setThreadNumber(_configData._threadNUm);
    _netIO.tcpAcceptor(_configData._serverPort);

    if (std::signal(SIGTERM, ::quitFunc) == SIG_ERR) {
        _utils.wirteLog(GLUtils::LL_ERROR, "Signale register error");
    }

    std::cout << "------------------------------------------------" << std::endl;
    std::cout << "\nMessage Server start OK!!\n\n" << std::endl;

    _utils.run();

}

} } // GreenLeaf::Server

