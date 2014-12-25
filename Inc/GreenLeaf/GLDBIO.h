/*
 * GLDBIO.h
 *
 *  Created on: Oct 30, 2014
 *      Author: wim
 */

#ifndef GLDBIO_H
#define GLDBIO_H

#if defined(__WIN32__)
    #if defined(GLDBIO_LIBRARY)
    #  define GLDBIO_SHARED_EXPORT __declspec(dllexport)
    #else
    #  define GLDBIO_SHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #define GLDBIO_SHARED_EXPORT
#endif

namespace GreenLeaf {
namespace GLDBIO {

enum DatabaseType {
    DT_NONE = 0,
    DT_MYSQL,
    DT_ORACLE,
    DT_MSSQL,
    DT_ODBC
};

class GLDBIO_SHARED_EXPORT DBIO: private boost::noncopyable
{
public:
    static DBIO& instance();

    const bool initMySqlConnectionPool(const std::string& serverAddr,
            const std::string& username,
            const std::string& passwd,
            const std::string& dbname,
            const std::size_t& maxSize);

    const std::vector<std::string> selectData(DatabaseType type, std::string& query);
    const bool insertData(DatabaseType type, const std::string& query);
    const bool deleteData(DatabaseType type, const std::string& query);
    const bool updateData(DatabaseType type, const std::string& query);
    const bool exec(DatabaseType type, const std::string& query);

};

} } // GreenLeaf::GLDBIO

#endif // GLDBIO_H

