/*
 * CHGHandler.h
 *
 *  Created on: Dec 8, 2014
 *      Author: wim
 */

#ifndef CHGHANDLER_H
#define CHGHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class CHGHandler: private HandlerCommon
{
public:
    explicit CHGHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleCHG();

};

} } // GreenLeaf::Server

#endif // CHGHANDLER_H

