/*
 * SLGVHandler.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/SLGVDefines.h"
#include "GreenLeaf/MsgServer/handlers/SLGVHandler.h"

namespace GreenLeaf {
namespace Server {

SLGVHandler::SLGVHandler(): HandlerCommon()
{
}

void SLGVHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(SLGV_RQ_METHON, msg->_methon);
    this->setTmpDataItem(SLGV_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(SLGV_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleSLGV();
    }
}

void SLGVHandler::operationNormal()
{

}

void SLGVHandler::operationException()
{
    this->setTmpDataItem(SLGV_E_METHON, "ERR");
    this->setTmpDataItem(SLGV_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(SLGV_E_CMDID, this->tmpDataValue(SLGV_RQ_CMDID));
    this->setTmpDataItem(SLGV_E_CMDNAME, this->tmpDataValue(SLGV_RQ_METHON));
    this->setTmpDataItem(SLGV_E_SCMDERID, "{9CB5224E-6A4D-41D6-AAAF-830F4362E0F0}");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void SLGVHandler::bundleMessage()
{

}

void SLGVHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(SLGV_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(SLGV_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(SLGV_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(SLGV_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(SLGV_E_SCMDERID));
}

void SLGVHandler::handleSLGV()
{
    _exceptionCode = ERR_FAR_SERVER_NOTSUPPORT;

    this->sendResponseMessage();

}




} } // GreenLeaf::Server

