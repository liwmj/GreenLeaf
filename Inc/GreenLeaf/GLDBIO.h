/**
 * @file GLDBIO.h
 * @brief GLDBIO库的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
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

/** 数据库类型枚举 */
enum DatabaseType {
    DT_NONE = 0,  /**< 默认无类型 */
    DT_MYSQL,     /**< mysql */
    DT_ORACLE,    /**< oracle */
    DT_MSSQL,     /**< sql server */
    DT_ODBC       /**< odbc */
};

/**
 * @brief GLDBIO库的接口类
 */
class GLDBIO_SHARED_EXPORT DBIO: private boost::noncopyable
{
public:
    /** DBIO的单例接口 */
    static DBIO& instance();

    /** 初始化MySql连接池 */
    const bool initMySqlConnectionPool(const std::string& serverAddr,
            const std::string& username,
            const std::string& passwd,
            const std::string& dbname,
            const std::size_t& maxSize);

    /** 查询一行或一列数据 */
    const std::vector<std::string> selectData(DatabaseType type, std::string& query);

    /** 插入一条数据 */
    const bool insertData(DatabaseType type, const std::string& query);

    /** 删除一条数据 */
    const bool deleteData(DatabaseType type, const std::string& query);

    /** 更新一条数据 */
    const bool updateData(DatabaseType type, const std::string& query);

    /** 执行一条语句 */
    const bool exec(DatabaseType type, const std::string& query);

};

} } // GreenLeaf::GLDBIO

#endif // GLDBIO_H

