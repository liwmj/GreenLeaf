/*
 * OracleConnectionPool.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: wim
 */

#include <boost/typeof/typeof.hpp>

#include "GreenLeaf/GLDBIO/OracleConnectionPool.h"

namespace GreenLeaf {
namespace GLDBIO {

OracleConnectionPool& OracleConnectionPool::instance()
{
    static OracleConnectionPool _gInstance;
    return _gInstance;
}

OracleConnectionPool::OracleConnectionPool(): super()
{
}

void OracleConnectionPool::setParam(const std::string& connStr, const std::size_t& maxSize)
{
    _connStr = connStr;
    _maxSize = maxSize;
}

OracleConnectionPool::ConnectionPtr OracleConnectionPool::connection()
{
    ConnectionPtr connPtr;

    std::time_t begin;
    std::time(&begin);

    while(1) {
        boost::mutex::scoped_lock lock(_mutex);

        if (_connContainer.size() == 0) {
            std::time_t now;
            std::time(&now);
            if (now - begin > 10) {
                createConnection();
                begin = now;
            }
            continue;
        }

        connPtr = _connContainer.front();
        _connContainer.pop_front();

        if (connPtr != NULL && connPtr->connected) {

            break;
        } else {
            this->createConnection();
            continue;;
        }
    }

    return connPtr;
}

const bool OracleConnectionPool::initConnection()
{
    bool isInit = false;

    _connContainer.resize(_maxSize);
    otl_connect::otl_initialize(1);

    for (int i = 0; i < _maxSize; ++i) {
        if (this->createConnection() != NULL)
            isInit = true;
    }

    return isInit;
}

OracleConnectionPool::ConnectionPtr OracleConnectionPool::createConnection()
{
    ConnectionPtr connPtr(new otl_connect);
    connPtr->rlogon(_connStr.c_str());

    if (connPtr != NULL && connPtr->connected) {
        connPtr->auto_commit_on();
        connPtr->set_timeout(60);
        _connContainer.push_back(connPtr);
    }

    return connPtr;
}

void OracleConnectionPool::releaseConnection(ConnectionPtr connPtr)
{
    boost::mutex::scoped_lock lock(_mutex);
    if (connPtr != NULL  && connPtr->connected) {
        _connContainer.push_back(connPtr);
    }
}

void OracleConnectionPool::checkDbConnections()
{

}

} } // GreenLeaf::GLDBIO

