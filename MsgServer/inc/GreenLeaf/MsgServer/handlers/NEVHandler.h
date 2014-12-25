/*
 * NEVHandler.h
 *
 *  Created on: Dec 5, 2014
 *      Author: wim
 */

#ifndef NEVHANDLER_H
#define NEVHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class NEVHandler: private HandlerCommon
{
public:
    explicit NEVHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleNEV();

};

} } // GreenLeaf::Server

#endif // NEVHANDLER_H

