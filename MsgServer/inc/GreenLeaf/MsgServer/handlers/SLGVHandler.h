/*
 * SLGVHandler.h
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#ifndef SLGVHANDLER_H
#define SLGVHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class SLGVHandler: private HandlerCommon
{
public:
    explicit SLGVHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleSLGV();

};

} } // GreenLeaf::Server

#endif // SLGVHANDLER_H

