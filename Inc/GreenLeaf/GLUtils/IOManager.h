/*
 * IOManager.h
 *
 *  Created on: Dec 10, 2014
 *      Author: wim
 */

#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <boost/asio.hpp>

namespace GreenLeaf {
namespace GLUtils {

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
    std::size_t _coreNumber;
    boost::asio::io_service _service;
    boost::asio::io_service::strand _strand;
    boost::shared_ptr<boost::asio::io_service::work> _work;

};

} } // GreenLeaf::GLUtils

#endif // IOMANAGER_H

