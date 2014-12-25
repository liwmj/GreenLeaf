/*
 * MySqlConnectionPool.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: wim
 */

#include <cstdio>
#include <iostream>
#include <vector>
#include <boost/typeof/typeof.hpp>

#include "GreenLeaf/GLDBIO/MySqlConnectionPool.h"

namespace GreenLeaf {
namespace GLDBIO {

MySqlConnectionPool& MySqlConnectionPool::instance()
{
    static MySqlConnectionPool _gInstance;
    return _gInstance;
}

MySqlConnectionPool::MySqlConnectionPool(): super()
{
}

void MySqlConnectionPool::setParam(const std::string& serverAddr,
        const std::string& username,
        const std::string& passwd,
        const std::string& dbname,
        const std::size_t& maxSize)
{
    _serverAddr = serverAddr;
    _username = username;
    _passwd = passwd;
    _dbname = dbname;
    if (maxSize)
        _maxSize = maxSize;
}

MySqlConnectionPool::ConnectionPtr MySqlConnectionPool::connection()
{
    ConnectionPtr connPtr(new MYSQL);

    std::time_t begin;
    std::time(&begin);

    while (1) {
        boost::mutex::scoped_lock lock(_mutex);

        if (_connContainer.size() == 0) {
            std::time_t now;
            std::time(&now);
            if (now - begin > 10) {
                this->createConnection();
                begin = now;
            }

            continue;
        }

        connPtr = _connContainer.front();
        _connContainer.pop_front();
        if (connPtr.get()) {
            break;

        } else {
            this->createConnection();
            continue;;
        }
    }

    return connPtr;
}

const bool MySqlConnectionPool::initConnection()
{
    bool isInit = false;
    _connContainer.resize(_maxSize);
    for (int i = 0; i < _maxSize; ++i) {
        if (this->createConnection().get())
            isInit = true;
    }
    return isInit;
}

MySqlConnectionPool::ConnectionPtr MySqlConnectionPool::createConnection()
{
    ConnectionPtr connPtr(new MYSQL);

    *connPtr = *(::mysql_init(NULL));

    if (!::mysql_real_connect(&*connPtr, _serverAddr.c_str(), _username.c_str(), _passwd.c_str(),
            _dbname.c_str(), 0, NULL, 0)) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        return connPtr;
    }

    if (::mysql_set_character_set(&*connPtr, "utf8")) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        return connPtr;
    }

    std::string query("SET SESSION TRANSACTION ISOLATION LEVEL READ COMMITTED;");
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        return connPtr;
    }
    query.clear();
    query = "USE "; query += _dbname; query += ";";
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        return connPtr;
    }
    query.clear();
    query = "SET GLOBAL init_connect='set autocommit=1';";
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        return connPtr;
    }

    if (connPtr.get()) {
        _connContainer.push_back(connPtr);

    }

    return connPtr;
}

void MySqlConnectionPool::releaseConnection(ConnectionPtr connPtr)
{
    boost::mutex::scoped_lock lock(_mutex);
    if (connPtr.get()) {
        _connContainer.push_back(connPtr);
    }
}

void MySqlConnectionPool::checkDbConnections()
{
    boost::mutex::scoped_lock lock(_mutex);

    int i = _connContainer.size();
    while (i) {
        ConnectionPtr connPtr(new MYSQL);
        connPtr = _connContainer.front();
        _connContainer.pop_front();

        std::string query("SELECT CURDATE();");

        if (!connPtr.get()) {
            std::cout << "startCheckDbConnection connPtr is null" << std::endl;
        }

        if (::mysql_ping(&*connPtr)) {
            std::cout << "mysql ping  is error" << std::endl;
        }

        if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
            std::cout << ::mysql_error(&*connPtr) << std::endl;

            ::mysql_close(&*connPtr);
            if (!::mysql_real_connect(&*connPtr, _serverAddr.c_str(), _username.c_str(), _passwd.c_str(),
                    _dbname.c_str(), 0, NULL, 0)) {
                std::cout << ::mysql_error(&*connPtr) << std::endl;
                this->createConnection();
            }

        } else {
            std::vector<std::string> resVector;
            MYSQL_RES *res;
            MYSQL_ROW row;

            res = ::mysql_store_result(&*connPtr);
            row = ::mysql_fetch_row(res);
            while (row) {
                for (int i = 0; i < ::mysql_num_fields(res); ++i) {
                    resVector.push_back(std::string(row[i]));
                }
                row = ::mysql_fetch_row(res);
            }
            ::mysql_free_result(res);
        }

        if (connPtr.get()) {
            _connContainer.push_back(connPtr);
        }

        --i;
    }
}

const std::vector<std::string> MySqlConnectionPool::selectData(std::string& query)
{
    std::vector<std::string> resVector;
    ConnectionPtr connPtr = this->connection();
    MYSQL_RES *res;
    MYSQL_ROW row;

    if (!connPtr.get()) {
        std::cout << "selectData connPtr is null" << std::endl;
    }

    if (::mysql_ping(&*connPtr)) {
        std::cout << "mysql ping  is error" << std::endl;
        return resVector;
    }

    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        this->releaseConnection(connPtr);
        return resVector;
    }

    res = ::mysql_store_result(&*connPtr);
    row = ::mysql_fetch_row(res);
    while (row) {
        for (int i = 0; i < ::mysql_num_fields(res); ++i) {
            resVector.push_back(std::string(row[i]));
        }
        row = ::mysql_fetch_row(res);
    }

    ::mysql_free_result(res);
    this->releaseConnection(connPtr);
    return resVector;
}

const bool MySqlConnectionPool::insertData(const std::string& query)
{
    ConnectionPtr connPtr = this->connection();
    if (!connPtr.get()) {
        std::cout << "insertData connPtr is null" << std::endl;
        return false;
    }
    if (::mysql_ping(&*connPtr)) {
        std::cout << "mysql ping  is error" << std::endl;
        return false;
    }
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        this->releaseConnection(connPtr);
        return false;
    }
    this->releaseConnection(connPtr);
    return true;
}

const bool MySqlConnectionPool::deleteData(const std::string& query)
{
    ConnectionPtr connPtr = this->connection();
    if (!connPtr.get()) {
        std::cout << "deleteData connPtr is null" << std::endl;
        return false;
    }
    if (::mysql_ping(&*connPtr)) {
        std::cout << "mysql ping  is error" << std::endl;
        return false;
    }
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        this->releaseConnection(connPtr);
        return false;
    }
    this->releaseConnection(connPtr);
    return true;
}

const bool MySqlConnectionPool::updateData(const std::string& query)
{
    ConnectionPtr connPtr = this->connection();
    if (!connPtr.get()) {
        std::cout << "updateData connPtr is null" << std::endl;
        return false;
    }
    if (::mysql_ping(&*connPtr)) {
        std::cout << "mysql ping  is error" << std::endl;
        return false;
    }
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        this->releaseConnection(connPtr);
        return false;
    }
    this->releaseConnection(connPtr);
    return true;
}

const bool MySqlConnectionPool::exec(const std::string& query)
{
    ConnectionPtr connPtr = this->connection();
    if (!connPtr.get()) {
        std::cout << "exec connPtr is null" << std::endl;
        return false;
    }
    if (::mysql_ping(&*connPtr)) {
        std::cout << "mysql ping  is error" << std::endl;
        return false;
    }
    if (::mysql_real_query(&*connPtr, query.c_str(), (unsigned int)strlen(query.c_str()))) {
        std::cout << ::mysql_error(&*connPtr) << std::endl;
        this->releaseConnection(connPtr);
        return false;
    }
    this->releaseConnection(connPtr);
    return true;
}


} } // GreenLeaf::GLDBIO
