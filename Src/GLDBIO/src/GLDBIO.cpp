/*
 * GLDBIO.cpp
 *
 *  Created on: Oct 30, 2014
 *      Author: wim
 */

#include <iostream>
#include <vector>
#include <string>

#include "GreenLeaf/GLDBIO/MySqlConnectionPool.h"

#include "GreenLeaf/GLDBIO.h"

namespace GreenLeaf {
namespace GLDBIO {

DBIO& DBIO::instance()
{
    static DBIO _gInstance;
    return _gInstance;
}

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

