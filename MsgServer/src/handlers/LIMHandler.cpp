/*
 * LIMHandler.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/LIMDefines.h"
#include "GreenLeaf/MsgServer/handlers/LIMHandler.h"

namespace GreenLeaf {
namespace Server {

LIMHandler::LIMHandler(): HandlerCommon()
{
}

void LIMHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(LIM_RQ_METHON, msg->_methon);
    this->setTmpDataItem(LIM_RQ_ITEMTYPE, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(LIM_RQ_ITEMID, this->paramItem(msg->_params, 1));
    this->setTmpDataItem(LIM_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(LIM_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleLIM();
    }
}

void LIMHandler::operationNormal()
{

}

void LIMHandler::operationException()
{
    this->setTmpDataItem(LIM_E_METHON, "ERR");
    this->setTmpDataItem(LIM_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(LIM_E_CMDID, this->tmpDataValue(LIM_RQ_CMDID));
    this->setTmpDataItem(LIM_E_CMDNAME, this->tmpDataValue(LIM_RQ_METHON));
    this->setTmpDataItem(LIM_E_SCMDERID, "{67C6799F-3B02-4462-A42C-B0025193C992}");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LIMHandler::bundleMessage()
{

    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LIMHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(LIM_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LIM_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(LIM_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(LIM_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(LIM_E_SCMDERID));

}

void LIMHandler::handleLIM()
{
    _exceptionCode = 402;

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

