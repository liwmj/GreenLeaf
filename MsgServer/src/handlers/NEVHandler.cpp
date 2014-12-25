/*
 * NEVHandler.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/NEVDefines.h"
#include "GreenLeaf/MsgServer/handlers/NEVHandler.h"

namespace GreenLeaf {
namespace Server {

NEVHandler::NEVHandler(): HandlerCommon()
{
}

void NEVHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(NEV_RQ_METHON, msg->_methon);
    this->setTmpDataItem(NEV_RQ_VIEWTYPE, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(NEV_RQ_VIEWNAME, this->paramItem(msg->_params, 1));
    this->setTmpDataItem(NEV_RQ_VIEWID, this->paramItem(msg->_params, 2));
    this->setTmpDataItem(NEV_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(NEV_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleNEV();
    }
}

void NEVHandler::operationNormal()
{

    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void NEVHandler::operationException()
{
    this->setTmpDataItem(NEV_E_METHON, "ERR");
    this->setTmpDataItem(NEV_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(NEV_E_CMDID, this->tmpDataValue(NEV_RQ_CMDID));
    this->setTmpDataItem(NEV_E_CMDNAME, this->tmpDataValue(NEV_RQ_METHON));
    this->setTmpDataItem(NEV_E_SCMDERID, "{67C6799F-3B02-4462-A42C-B0025193C992}");

    this->bundleErrorMessage();
    _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void NEVHandler::bundleMessage()
{

}

void NEVHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(NEV_E_METHON));

    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(NEV_E_ERRORCODE));

    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(NEV_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(NEV_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(NEV_E_SCMDERID));

}

void NEVHandler::handleNEV()
{
    _exceptionCode = 402;

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

