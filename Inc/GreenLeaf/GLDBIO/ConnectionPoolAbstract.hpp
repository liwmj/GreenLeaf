/**
 * @file ConnectionPoolAbstract.hpp
 * @brief 连接池抽象基类的声明与实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef CONNECTIONPOOLABSTRACT_h
#define CONNECTIONPOOLABSTRACT_h

#include <iostream>
#include <string>
#include <vector>
#include <boost/bind.hpp>
#include <boost/circular_buffer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "GreenLeaf/GLUtils.h"

namespace GreenLeaf {
namespace GLDBIO {

/**
 * @brief 连接池的抽象基类
 * @tparam Conn 数据库连接对象
 */
template <class Conn>
class ConnectionPoolAbstract
{
public:
    typedef Conn Connection;
    typedef boost::shared_ptr<Conn> ConnectionPtr;

    /**
     * @brief 获取连接池大小
     * @return 返回连接池大小
     */
    inline int size() { return _connContainer.size(); }

    /**
     * @brief 定时检查数据库连接
     */
    void startCheckConnection() {
        this->checkDbConnections();
        _dbTimer.expires_from_now(boost::posix_time::seconds(4 * 60 * 60));
        _dbTimer.async_wait(boost::bind(&ConnectionPoolAbstract::startCheckConnection, this));
    }

    virtual ConnectionPtr connection() = 0;
    virtual const bool initConnection() = 0;
    virtual ConnectionPtr createConnection() = 0;
    virtual void releaseConnection(ConnectionPtr ptrConn) = 0;
    virtual void checkDbConnections() {}

    /**
     * @brief 初始化ConnectionPoolAbstract对象
     * @param
     */
    ConnectionPoolAbstract(): _maxSize(1),
            _dbIOService(GLUtils::Utils::instance().ioService()),
            _dbTimer(_dbIOService) { this->startCheckConnection(); }

    /**
     * @brief 析构ConnectionPoolAbstract对象
     */
    virtual ~ConnectionPoolAbstract() {
        boost::system::error_code ec;
        _dbTimer.cancel(ec);
        _dbTimer.expires_at(boost::posix_time::pos_infin);
    }

protected:
    typedef boost::circular_buffer_space_optimized<ConnectionPtr> ConnectionCirular;

    ConnectionCirular _connContainer;       /**< 存储数据库连接的容器 */
    std::size_t _maxSize;                   /**< 连接池的大小 */

    boost::asio::io_service& _dbIOService;  /**< 连接池所需io */
    boost::asio::deadline_timer _dbTimer;   /**< 连接检查器 */

    boost::mutex _mutex;                    /**< 多线程所需锁 */

};

} } // GreenLeaf::GLDBIO

#endif // CONNECTIONPOOLABSTRACT_h

