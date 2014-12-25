/*
 * HandlerManager.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/MsgServer/handlers/GETHandler.h"
#include "GreenLeaf/MsgServer/handlers/CCLHandler.h"
#include "GreenLeaf/MsgServer/handlers/CUSHandler.h"
#include "GreenLeaf/MsgServer/handlers/USRHandler.h"
#include "GreenLeaf/MsgServer/handlers/LSVHandler.h"
#include "GreenLeaf/MsgServer/handlers/LGVHandler.h"
#include "GreenLeaf/MsgServer/handlers/SLGVHandler.h"
#include "GreenLeaf/MsgServer/handlers/SCOPHandler.h"
#include "GreenLeaf/MsgServer/handlers/LCAHandler.h"
#include "GreenLeaf/MsgServer/handlers/RUSHandler.h"
#include "GreenLeaf/MsgServer/handlers/NEVHandler.h"
#include "GreenLeaf/MsgServer/handlers/LIMHandler.h"
#include "GreenLeaf/MsgServer/handlers/CHGHandler.h"

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
    this->loginCmder();
    this->statusCmder();

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
    _registered &= this->initHandler<GETHandler>("GET");
    _registered &= this->initHandler<CCLHandler>("CCL");
    _registered &= this->initHandler<CUSHandler>("CUS");
}

void HandlerManager::loginCmder()
{
    _registered &= this->initHandler<USRHandler>("USR");
    _registered &= this->initHandler<LSVHandler>("LSV");
    _registered &= this->initHandler<LGVHandler>("LGV");
    _registered &= this->initHandler<LCAHandler>("LCA");
    _registered &= this->initHandler<NEVHandler>("NEV");
    _registered &= this->initHandler<LIMHandler>("LIM");
    _registered &= this->initHandler<SLGVHandler>("SLGV");
    _registered &= this->initHandler<SCOPHandler>("SCOP");
}

void HandlerManager::statusCmder()
{
    _registered &= this->initHandler<CHGHandler>("CHG");
    _registered &= this->initHandler<RUSHandler>("RUS");
}

} } // GreenLeaf::Server

