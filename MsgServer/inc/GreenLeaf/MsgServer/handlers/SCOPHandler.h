/*
 * SCOPHandler.h
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#ifndef SCOPHANDLER_H
#define SCOPHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class SCOPHandler: private HandlerCommon
{
public:
    explicit SCOPHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleSCOP();

};

} } // GreenLeaf::Server

#endif // SCOPHANDLER_H

