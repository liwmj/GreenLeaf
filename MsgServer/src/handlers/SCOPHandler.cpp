/*
 * SCOPHandler.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/SCOPDefines.h"
#include "GreenLeaf/MsgServer/handlers/SCOPHandler.h"

namespace GreenLeaf {
namespace Server {

SCOPHandler::SCOPHandler(): HandlerCommon()
{
}

void SCOPHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(SCOP_RQ_METHON, msg->_methon);
    this->setTmpDataItem(SCOP_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(SCOP_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleSCOP();
    }
}


void SCOPHandler::operationNormal()
{
    this->bundleMessage();
    _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void SCOPHandler::operationException()
{
    this->setTmpDataItem(SCOP_E_METHON, "ERR");
    this->setTmpDataItem(SCOP_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(SCOP_E_CMDID, this->tmpDataValue(SCOP_RQ_CMDID));
    this->setTmpDataItem(SCOP_E_CMDNAME, this->tmpDataValue(SCOP_RQ_METHON));
    this->setTmpDataItem(SCOP_E_SCMDERID, "{9CB5224E-6A4D-41D6-AAAF-830F4362E0F0}");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void SCOPHandler::bundleMessage()
{

}

void SCOPHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(SCOP_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(SCOP_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(SCOP_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(SCOP_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(SCOP_E_SCMDERID));
}

void SCOPHandler::handleSCOP()
{
    _exceptionCode = 402;

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

