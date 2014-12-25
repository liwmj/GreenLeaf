/*
 * IOManager.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: wim
 */

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "GreenLeaf/GLUtils/IOManager.h"

namespace GreenLeaf {
namespace GLUtils {

IOManager& IOManager::instance()
{
    static IOManager _gInstance;
    return _gInstance;
}

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

void IOManager::setThreadNumber(const std::size_t& num)
{
    _coreNumber = num;
}

const std::size_t& IOManager::threadNumber() const
{
    return _coreNumber;
}

boost::asio::io_service& IOManager::ioService()
{
    return _service;
}

boost::asio::io_service::strand& IOManager::strand()
{
    return _strand;
}

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

void IOManager::stop()
{
    _work.reset();
    _service.stop();
}

} } // GreenLeaf::GLUtils

