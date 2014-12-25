/*
 * RUSHandler.h
 *
 *  Created on: Dec 3, 2014
 *      Author: wim
 */

#ifndef RUSHANDLER_H
#define RUSHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class RUSHandler: private HandlerCommon
{
public:
    enum CmdType {
        CT_RUS = 0,
        CT_NTE
    };
    explicit RUSHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleRUS();

private:
    CmdType _cmdType;

};

} } // GreenLeaf::Server

#endif // RUSHANDLER_H

