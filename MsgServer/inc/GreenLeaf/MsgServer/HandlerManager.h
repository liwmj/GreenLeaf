/*
 * HandlerManager.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#ifndef HANDLERMANAGER_H
#define HANDLERMANAGER_H

#include "GreenLeaf/GLNetIO.h"

namespace GreenLeaf {
namespace Server {

class HandlerManager: private boost::noncopyable
{
public:
    static HandlerManager& instance();

    const bool registerAllHandlers();

private:
    explicit HandlerManager();

    template<class Handler>
    const bool initHandler(const std::string cmd);

    template<class Handler>
    void notifyHandler(GLNetIO::RequestBufferPtr msg);

    void baseCmder();
    void loginCmder();
    void statusCmder();

private:
    bool _registered;

};

} } // GreenLeaf::Server

#endif // HANDLERMANAGER_H

