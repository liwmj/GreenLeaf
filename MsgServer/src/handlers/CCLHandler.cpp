/*
 * CCLHandler.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/CCLDefines.h"
#include "GreenLeaf/MsgServer/handlers/CCLHandler.h"

namespace GreenLeaf {
namespace Server {

CCLHandler::CCLHandler(): HandlerCommon()
{
}

void CCLHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(CCL_RQ_METHON, msg->_methon);
    this->setTmpDataItem(CCL_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(CCL_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    this->setTmpDataItem(CCL_RQ_ISMAST, this->propValue(msg->_props, "ismast"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleCCL();
    }
}

void CCLHandler::operationNormal()
{
    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void CCLHandler::operationException()
{
    this->setTmpDataItem(CCL_E_METHON, "ERR");
    this->setTmpDataItem(CCL_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(CCL_E_CMDID, this->tmpDataValue(CCL_RQ_CMDID));
    this->setTmpDataItem(CCL_E_CMDNAME, this->tmpDataValue(CCL_RQ_METHON));
    this->setTmpDataItem(CCL_E_SCMDERID, "");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void CCLHandler::bundleMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(CCL_RS_METHON));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(CCL_RS_CMDID));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(CCL_RS_SCMDERID));
}

void CCLHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(CCL_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(CCL_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(CCL_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(CCL_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(CCL_E_SCMDERID));
}

void CCLHandler::handleCCL()
{
    this->setTmpDataItem(CCL_RS_METHON, this->tmpDataValue(CCL_RQ_METHON));
    this->setTmpDataItem(CCL_RS_CMDID, this->tmpDataValue(CCL_RQ_CMDID));
    this->setTmpDataItem(CCL_RS_SCMDERID, "");

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

