/*
 * MSSqlConnectionPool.cpp
 *
 *  Created on: Nov 20, 2014
 *      Author: wim
 */

#include <boost/typeof/typeof.hpp>

#include "GreenLeaf/GLDBIO/MSSqlConnectionPool.h"

namespace GreenLeaf {
namespace GLDBIO {

MSSqlConnectionPool& MSSqlConnectionPool::instance()
{
    static MSSqlConnectionPool _gInstance;
    return _gInstance;
}

MSSqlConnectionPool::MSSqlConnectionPool(): super()
{
}

void MSSqlConnectionPool::setParam(const std::string& connStr, const std::size_t& maxSize)
{
    _connStr = connStr;
    _maxSize = maxSize;
}

MSSqlConnectionPool::ConnectionPtr MSSqlConnectionPool::connection()
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

const bool MSSqlConnectionPool::initConnection()
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

MSSqlConnectionPool::ConnectionPtr MSSqlConnectionPool::createConnection()
{
    ConnectionPtr ptrConn(new otl_connect);
    ptrConn->rlogon(_connStr.c_str());

    if (ptrConn != NULL && ptrConn->connected) {
        ptrConn->auto_commit_on();
        ptrConn->set_timeout(60);
        _connContainer.push_back(ptrConn);
    }

    return ptrConn;
}

void MSSqlConnectionPool::releaseConnection(ConnectionPtr connPtr)
{
    boost::mutex::scoped_lock lock(_mutex);
    if (connPtr != NULL  && connPtr->connected) {
        _connContainer.push_back(connPtr);
    }
}

void MSSqlConnectionPool::checkDbConnections()
{

}



} } // GreenLeaf::GLDBIO



