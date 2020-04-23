/**
 * @file MSSqlConnectionPool.cpp
 * @brief SqlServer连接池的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/typeof/typeof.hpp>

#include "GreenLeaf/GLDBIO/MSSqlConnectionPool.h"

namespace GreenLeaf {
namespace GLDBIO {

/**
 * @brief 创建MSSqlConnectionPool单例对象
 * @return 返回MSSqlConnectionPool对象
 */
MSSqlConnectionPool& MSSqlConnectionPool::instance()
{
    static MSSqlConnectionPool _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化MSSqlConnectionPool对象
 * @param super
 */
MSSqlConnectionPool::MSSqlConnectionPool(): super()
{
}

/**
 * @brief 设置SQL Server连接参数
 * @param connStr 具体连接参数
 * @param maxSize 连接池大小
 */
void MSSqlConnectionPool::setParam(const std::string& connStr, const std::size_t& maxSize)
{
    _connStr = connStr;
    _maxSize = maxSize;
}

/**
 * @brief 获取一条SQL Server数据库连接
 * @return 返回SQL Server数据库连接指针
 */
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

/**
 * @brief 初始化SQL Server连接
 * @return 返回是否初始化成功
 */
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

/**
 * @brief 创建SQL Server数据库连接
 * @return 返回SQL Server连接指针
 */
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

/**
 * @brief 释放SQL Server数据库连接
 * @param connPtr 指定释放的数据库连接
 */
void MSSqlConnectionPool::releaseConnection(ConnectionPtr connPtr)
{
    boost::mutex::scoped_lock lock(_mutex);
    if (connPtr != NULL  && connPtr->connected) {
        _connContainer.push_back(connPtr);
    }
}

/**
 * @brief 检测SQL Server连接
 */
void MSSqlConnectionPool::checkDbConnections()
{

}



} } // GreenLeaf::GLDBIO



