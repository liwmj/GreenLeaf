/*
 * LGVHandler.h
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#ifndef LGVHANDLER_H
#define LGVHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class LGVHandler: private HandlerCommon
{
public:
    explicit LGVHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleLGV();

    void redundantMsg();


};

} } // GreenLeaf::Server

#endif // LGVHANDLER_H

