/*
 * HandlerManager.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/MsgServer/handlers/CCLHandler.h"

#include "GreenLeaf/MsgServer/HandlerManager.h"

namespace GreenLeaf {
namespace Server {

HandlerManager& HandlerManager::instance()
{
    static HandlerManager _gInstance;
    return _gInstance;
}

HandlerManager::HandlerManager(): _registered(true)
{
}

const bool HandlerManager::registerAllHandlers()
{
    this->baseCmder();

    return _registered;
}

template<class Handler>
const bool HandlerManager::initHandler(const std::string cmd)
{
    bool registered = GLNetIO::MsgHandlerRepository<GLNetIO::RequestHandler>::instance().registerHandler(
            cmd,
            boost::bind(&HandlerManager::notifyHandler<Handler>, this, _1));
    return registered;
}

template<class Handler>
void HandlerManager::notifyHandler(GLNetIO::RequestBufferPtr msg)
{
    Handler handler;
    handler.handleMessage(msg);
}

void HandlerManager::baseCmder()
{
    _registered &= this->initHandler<CCLHandler>("CCL");
}

} } // GreenLeaf::Server

