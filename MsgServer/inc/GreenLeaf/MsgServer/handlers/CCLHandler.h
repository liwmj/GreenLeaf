/*
 * CCLHandler.h
 *
 *  Created on: Dec 1, 2014
 *      Author: Mason
 */

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class CCLHandler: private HandlerCommon
{
public:
    explicit CCLHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleCCL();


};

} } // GreenLeaf::Server

