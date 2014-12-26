/**
 * @file GLDBIO.cpp
 * @brief 数据库模块接口的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <vector>
#include <string>

#include "GreenLeaf/GLDBIO/MySqlConnectionPool.h"

#include "GreenLeaf/GLDBIO.h"

namespace GreenLeaf {
namespace GLDBIO {

/**
 * @brief 创建DBIO库的单例对象
 * @return 返回DBIO库的对象
 */
DBIO& DBIO::instance()
{
    static DBIO _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化MySql连接池
 * @param serverAddr MySql服务器ip
 * @param username MySql用户名
 * @param passwd MySql密码
 * @param dbname 指定使用的MySql库
 * @param maxSize MySql连接池大小
 * @return 返回初始化是否成功
 */
const bool DBIO::initMySqlConnectionPool(const std::string& serverAddr,
        const std::string& username,
        const std::string& passwd,
        const std::string& dbname,
        const std::size_t& maxSize)
{
    MySqlConnectionPool& mysqlPool = MySqlConnectionPool::instance();
    mysqlPool.setParam(serverAddr, username, passwd, dbname, maxSize);
    if (!mysqlPool.initConnection()) {
        return false;
    }

    return true;
}

/**
 * @brief 查询数据库数据
 * @param type 数据库类型
 * @param query 查询语句
 * @return 返回查询到的一行或一列数据
 */
const std::vector<std::string> DBIO::selectData(DatabaseType type, std::string& query)
{
    std::vector<std::string> vecRes;
    switch (type) {
    case DT_MYSQL:
        vecRes = MySqlConnectionPool::instance().selectData(query);
        break;
    case DT_ORACLE:
        break;
    case DT_MSSQL:
        break;
    case DT_ODBC:
        break;
    default:
        break;
    }
    return vecRes;
}

/**
 * @brief 删除一条数据库数据
 * @param type 数据库类型
 * @param query 查询语句
 * @return 返回是否删除成功
 */
const bool DBIO::deleteData(DatabaseType type, const std::string& query)
{
    bool isExec = false;
    switch (type) {
    case DT_MYSQL:
        isExec = MySqlConnectionPool::instance().deleteData(query);
        break;
    case DT_ORACLE:
        break;
    case DT_MSSQL:
        break;
    case DT_ODBC:
        break;
    default:
        break;
    }
    return isExec;
}

/**
 * @brief 更新一条数据库数据
 * @param type 数据库类型
 * @param query 查询语句
 * @return 返回更新数据是否成功
 */
const bool DBIO::updateData(DatabaseType type, const std::string& query)
{
    bool isExec = false;
    switch (type) {
    case DT_MYSQL:
        isExec = MySqlConnectionPool::instance().updateData(query);
        break;
    case DT_ORACLE:
        break;
    case DT_MSSQL:
        break;
    case DT_ODBC:
        break;
    default:
        break;
    }
    return isExec;
}

/**
 * @brief 执行一条查询语句
 * @param type 数据库类型
 * @param query 查询语句
 * @return 返回执行是否成功
 */
const bool DBIO::exec(DatabaseType type, const std::string& query)
{
    bool isExec = false;
    switch (type) {
    case DT_MYSQL:
        isExec = MySqlConnectionPool::instance().exec(query);
        break;
    case DT_ORACLE:
        break;
    case DT_MSSQL:
        break;
    case DT_ODBC:
        break;
    default:
        break;
    }
    return isExec;
}

} } // GreenLeaf::GLDBIO

