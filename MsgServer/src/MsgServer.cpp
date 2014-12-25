/*
 * DemoServer.cpp
 *
 *  Created on: NOv 4, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/MsgServerImpl.h"

#include "GreenLeaf/MsgServer/MsgServer.h"

namespace GreenLeaf {
namespace Server {

MsgServer::MsgServer():
        _pImpl(new MsgServerImpl)
{
}

MsgServer::~MsgServer()
{
    if (_pImpl)
        delete _pImpl;
}

void MsgServer::run() const
{
    _pImpl->run();
}

void MsgServer::stop() const
{
    _pImpl->stop();
}

} } // GreenLeaf::Server

