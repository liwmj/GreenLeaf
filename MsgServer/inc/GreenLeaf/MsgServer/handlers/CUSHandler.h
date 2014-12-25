/*
 * CUSHandler.h
 *
 *  Created on: Dec 5, 2014
 *      Author: wim
 */

#ifndef CUSHANDLER_H
#define CUSHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class CUSHandler: private HandlerCommon
{
public:
    explicit CUSHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleCUS();

};

} } // GreenLeaf::Server

#endif // CUSHANDLER_H

