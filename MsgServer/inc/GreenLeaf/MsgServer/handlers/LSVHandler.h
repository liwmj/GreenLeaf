/*
 * LSVHandler.h
 *
 *  Created on: Dec 1, 2014
 *      Author: wim
 */

#ifndef LSVHANDLER_h
#define LSVHANDLER_h

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class LSVHandler: private HandlerCommon
{
public:
    explicit LSVHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleLSV();

    void redundantMsg();

};

} } // GreenLeaf::Server

#endif // LSVHANDLER_h

