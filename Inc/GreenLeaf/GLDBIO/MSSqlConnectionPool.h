/*
 * OdbcConnectionPool.h
 *
 *  Created on: Nov 20, 2014
 *      Author: wim
 */

#ifndef ODBCCONNECTIONPOOL_H
#define ODBCCONNECTIONPOOL_H

#include <iostream>
using namespace std;
#include <stdio.h>
#define OTL_STL
#define OTL_ODBC // CompileOTL 4.0/ODBCx
#if defined(__WIN32__)
#else
    #define OTL_ODBC_UNIX
#endif
#define OTL_ODBC_MSSQL_2008 // Compile OTL 4/ODBC, MS SQL 2008

#include <boost/format.hpp>
#include <otlv4_h/otlv4.h>

#include "GreenLeaf/GLDBIO/ConnectionPoolAbstract.hpp"

namespace GreenLeaf {
namespace GLDBIO {

class MSSqlConnectionPool: private boost::noncopyable, public ConnectionPoolAbstract<otl_connect>
{
public:
    static MSSqlConnectionPool& instance();
    explicit MSSqlConnectionPool();

    void setParam(const std::string& connStr, const std::size_t& maxSize);

    virtual ConnectionPtr connection();
    virtual const bool initConnection();
    virtual ConnectionPtr createConnection();
    virtual void releaseConnection(ConnectionPtr connPtr);
    virtual void checkDbConnections();

private:
    typedef ConnectionPoolAbstract<otl_connect> super;

private:
    std::string _connStr;

};


} } // GreenLeaf::GLDBIO

#endif // ODBCCONNECTIONPOOL_H

