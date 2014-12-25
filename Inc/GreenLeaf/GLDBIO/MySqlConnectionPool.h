/*
 * MySqlConnectionPool.h
 *
 *  Created on: Nov 20, 2014
 *      Author: wim
 */

#ifndef MYSQLCONNECTIONPOOL_H
#define MYSQLCONNECTIONPOOL_H

#include <iostream>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <mysql/mysql.h>

#include "GreenLeaf/GLDBIO/ConnectionPoolAbstract.hpp"

namespace GreenLeaf {
namespace GLDBIO {

class MySqlConnectionPool: private boost::noncopyable, public ConnectionPoolAbstract<MYSQL>
{
public:
    static MySqlConnectionPool& instance();

    explicit MySqlConnectionPool();

    void setParam(const std::string& serverAddr,
            const std::string& username,
            const std::string& passwd,
            const std::string& dbname,
            const std::size_t& maxSize);

    virtual ConnectionPtr connection();
    virtual const bool initConnection();
    virtual ConnectionPtr createConnection();
    virtual void releaseConnection(ConnectionPtr connPtr);
    virtual void checkDbConnections();

    const std::vector<std::string> selectData(std::string& query);
    const bool insertData(const std::string& query);
    const bool deleteData(const std::string& query);
    const bool updateData(const std::string& query);
    const bool exec(const std::string& query);

private:
    typedef ConnectionPoolAbstract<MYSQL> super;

private:
    std::string _serverAddr;
    std::string _username;
    std::string _passwd;
    std::string _dbname;

};


} } // GreenLeaf::GLDBIO

#endif // MYSQLCONNECTIONPOOL_H

