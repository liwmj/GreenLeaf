/*
 * GETHandler.h
 *
 *  Created on: Nov 25, 2014
 *      Author: wim
 */

#ifndef GETHANDLER_H
#define GETHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class GETHandler: private HandlerCommon
{
public:
    explicit GETHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleGET();


};


} } // GreenLeaf::Server

#endif // GETHANDLER_H

