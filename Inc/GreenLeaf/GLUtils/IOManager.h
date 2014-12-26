/**
 * @file IOManager.h
 * @brief IO管理的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <boost/asio.hpp>

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief IO管理类
 */
class IOManager: private boost::noncopyable
{
public:
    static IOManager& instance();

    void setThreadNumber(const std::size_t& num);
    const std::size_t& threadNumber() const;

    boost::asio::io_service& ioService();
    boost::asio::io_service::strand& strand();

    void run();
    void stop();

private:
    explicit IOManager();

private:
    std::size_t _coreNumber;                                /**< io数量 */
    boost::asio::io_service _service;                       /**< 需要用到的io */
    boost::asio::io_service::strand _strand;                /**< 多线程io */
    boost::shared_ptr<boost::asio::io_service::work> _work; /**< 工作io */

};

} } // GreenLeaf::GLUtils

#endif // IOMANAGER_H

