/*
 * ConnectionPoolAbstract.h
 *
 *  Created on: Nov 19, 2014
 *      Author: wim
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

template <class Conn>
class ConnectionPoolAbstract
{
public:
    typedef Conn Connection;
    typedef boost::shared_ptr<Conn> ConnectionPtr;

    inline int size() { return _connContainer.size(); }
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

    ConnectionPoolAbstract(): _maxSize(1),
            _dbIOService(GLUtils::Utils::instance().ioService()),
            _dbTimer(_dbIOService) { this->startCheckConnection(); }
    virtual ~ConnectionPoolAbstract() {
        boost::system::error_code ec;
        _dbTimer.cancel(ec);
        _dbTimer.expires_at(boost::posix_time::pos_infin);
    }

protected:
    typedef boost::circular_buffer_space_optimized<ConnectionPtr> ConnectionCirular;

    ConnectionCirular _connContainer;
    std::size_t _maxSize;

    boost::asio::io_service& _dbIOService;
    boost::asio::deadline_timer _dbTimer;

    boost::mutex _mutex;

};

} } // GreenLeaf::GLDBIO

#endif // CONNECTIONPOOLABSTRACT_h

