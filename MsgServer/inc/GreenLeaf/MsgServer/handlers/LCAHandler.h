/*
 * LCAHandler.h
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#ifndef LCAHANDLER_H
#define LCAHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class LCAHandler: private HandlerCommon
{
public:
    explicit LCAHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleLCA();
};

} } // GreenLeaf::Server

#endif // LCAHANDLER_H

