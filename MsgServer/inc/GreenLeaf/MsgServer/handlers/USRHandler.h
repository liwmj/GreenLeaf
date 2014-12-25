/*
 * USRHandler.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#ifndef USRHANDLER_H
#define USRHANDLER_H

#include "GreenLeaf/MsgServer/HandlerCommon.h"

namespace GreenLeaf {
namespace Server {

class USRHandler: private HandlerCommon
{
public:
    explicit USRHandler();
    virtual void handleMessage(GLNetIO::RequestBufferPtr msg);

protected:
    virtual void operationNormal();
    virtual void operationException();
    virtual void bundleMessage();
    virtual void bundleErrorMessage();

private:
    void handleUSR();
    void handleUSR_L();
    void handleUSR_R();

    void operationERR();
    void operationOUT();

    const bool verifyUser();
    const bool verifyPasswd();
    const bool isKillUser();

    void userType();

    const bool updateCacheData(const std::string& loginName);

    void redundantMsg();

private:
    std::string _sessionType;
    std::string _userType;

};


} } // GreenLeaf::Server

#endif // USRHANDLER_H

