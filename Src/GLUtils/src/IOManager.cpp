/**
 * @file IOManager.cpp
 * @brief IO管理的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "GreenLeaf/GLUtils/IOManager.h"

namespace GreenLeaf {
namespace GLUtils {

/**
 * @brief 创建IOManager的单例对象
 * @return 返回IOManager对象
 */
IOManager& IOManager::instance()
{
    static IOManager _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化IOManager对象
 * @param
 */
IOManager::IOManager():
        _coreNumber(boost::thread::hardware_concurrency()),
        _service(),
        _strand(_service),
        _work(new boost::asio::io_service::work(_service))
{
    if (!_coreNumber) {
        _coreNumber = 32;
    } else {
        _coreNumber *= 2;
        _coreNumber += 2;
    }
}

/**
 * @brief 设置工作线程数
 * @param num 指定线程数
 */
void IOManager::setThreadNumber(const std::size_t& num)
{
    _coreNumber = num;
}

/**
 * @brief 获取工作线程数
 * @return 返回工作线程数
 */
const std::size_t& IOManager::threadNumber() const
{
    return _coreNumber;
}

/**
 * @brief 获取io service
 * @return 返回io service
 */
boost::asio::io_service& IOManager::ioService()
{
    return _service;
}

/**
 * @brief 获取io service
 * @return 返回io service
 */
boost::asio::io_service::strand& IOManager::strand()
{
    return _strand;
}

/**
 * @brief 运行所有io
 */
void IOManager::run()
{
    if (!_coreNumber) {
        _coreNumber = boost::thread::hardware_concurrency();
        if (!_coreNumber) {
            _coreNumber = 32;
        } else {
            _coreNumber *= 2;
            _coreNumber += 2;
        }
    }
    std::size_t n = _coreNumber;
    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (std::size_t i = 0; i < n; ++i) {
        boost::shared_ptr<boost::thread> thread(new boost::thread(
                        boost::bind(&boost::asio::io_service::run, &_service)));
        threads.push_back(thread);
    }

    for (std::size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
}

/**
 * @brief 停止所有io
 */
void IOManager::stop()
{
    _work.reset();
    _service.stop();
}

} } // GreenLeaf::GLUtils

