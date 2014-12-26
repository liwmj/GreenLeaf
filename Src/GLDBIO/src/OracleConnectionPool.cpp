/**
 * @file OracleConnectionPool.cpp
 * @brief Oracle连接池的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/typeof/typeof.hpp>

#include "GreenLeaf/GLDBIO/OracleConnectionPool.h"

namespace GreenLeaf {
namespace GLDBIO {

/**
 * @brief 创建OracleConnectionPool单例对象
 * @return 返回OracleConnectionPool对象
 */
OracleConnectionPool& OracleConnectionPool::instance()
{
    static OracleConnectionPool _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化OracleConnectionPool对象
 * @param super
 */
OracleConnectionPool::OracleConnectionPool(): super()
{
}

/**
 * @brief 设置orace连接信息
 * @param connStr 具体的连接信息
 * @param maxSize 连接池大小
 */
void OracleConnectionPool::setParam(const std::string& connStr, const std::size_t& maxSize)
{
    _connStr = connStr;
    _maxSize = maxSize;
}

/**
 * @brief 获取orace数据库连接
 * @return 返回一个orace连接
 */
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

/**
 * @brief 初始化orace连接池
 * @return 返回初始化是否成功
 */
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

/**
 * @brief 创建orace数据库连接
 * @return 返回orace连接的指针
 */
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

/**
 * @brief 释放orace数据库连接
 * @param connPtr 指定需释放的连接
 */
void OracleConnectionPool::releaseConnection(ConnectionPtr connPtr)
{
    boost::mutex::scoped_lock lock(_mutex);
    if (connPtr != NULL  && connPtr->connected) {
        _connContainer.push_back(connPtr);
    }
}

/**
 * @brief 检测orace连接
 */
void OracleConnectionPool::checkDbConnections()
{

}

} } // GreenLeaf::GLDBIO

