/*
 * RUSHandler.cpp
 *
 *  Created on: Dec 3, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/RUSDefines.h"
#include "GreenLeaf/MsgServer/handlers/RUSHandler.h"

namespace GreenLeaf {
namespace Server {

RUSHandler::RUSHandler(): HandlerCommon(), _cmdType(CT_RUS)
{
}

void RUSHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(RUS_RQ_METHON, msg->_methon);
    this->setTmpDataItem(RUS_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(RUS_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    this->setTmpDataItem(RUS_RQ_CONTENTLENGTH, this->propValue(msg->_props, "content-length"));
    this->setTmpDataItem(RUS_RQ_BODY, msg->_body);
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleRUS();
    }
}

void RUSHandler::operationNormal()
{
    this->setTmpDataItem(RUS_RS_METHON, "RUS");
    this->setTmpDataItem(RUS_RS_CMDID, this->tmpDataValue(RUS_RQ_CMDID));
    this->setTmpDataItem(RUS_RS_SCMDERID, "{062EE77B-9DED-43D4-A751-BDF208188D0D}");

    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void RUSHandler::operationException()
{
    this->setTmpDataItem(RUS_E_METHON, "ERR");
    this->setTmpDataItem(RUS_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(RUS_E_CMDID, this->tmpDataValue(RUS_RQ_CMDID));
    this->setTmpDataItem(RUS_E_CMDNAME, this->tmpDataValue(RUS_RQ_METHON));
    this->setTmpDataItem(RUS_E_SCMDERID, "{062EE77B-9DED-43D4-A751-BDF208188D0D}");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);

}

void RUSHandler::bundleMessage()
{
    if (_cmdType == CT_RUS) {
        this->setMethon(_responseBuffer->_methon, this->tmpDataValue(RUS_RS_METHON));
        this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(RUS_RS_CMDID));
        this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(RUS_RS_SCMDERID));

    } else if (_cmdType == CT_NTE) {

    }
}

void RUSHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(RUS_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(RUS_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(RUS_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(RUS_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(RUS_E_SCMDERID));
}

void RUSHandler::handleRUS()
{
//    _exceptionCode = 402;

    this->sendResponseMessage();
}


} } // GreenLeaf::Server

