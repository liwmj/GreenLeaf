/*
 * LIMHandler.h
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#ifndef LIMHANDLER_H
#define LIMHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class LIMHandler: private HandlerCommon
{
public:
    explicit LIMHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleLIM();

};

} } // GreenLeaf::Server

#endif // LIMHANDLER_H

