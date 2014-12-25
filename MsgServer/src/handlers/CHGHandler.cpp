/*
 * CHGHandler.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/CHGDefines.h"
#include "GreenLeaf/MsgServer/handlers/CHGHandler.h"

namespace GreenLeaf {
namespace Server {

CHGHandler::CHGHandler(): HandlerCommon()
{
}

void CHGHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(CHG_RQ_METHON, msg->_methon);
    this->setTmpDataItem(CHG_RQ_STATUS, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(CHG_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(CHG_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleCHG();
    }
}

void CHGHandler::operationNormal()
{

}

void CHGHandler::operationException()
{
    this->setTmpDataItem(CHG_E_METHON, "ERR");
    this->setTmpDataItem(CHG_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(CHG_E_CMDID, this->tmpDataValue(CHG_RQ_CMDID));
    this->setTmpDataItem(CHG_E_CMDNAME, this->tmpDataValue(CHG_RQ_METHON));
    this->setTmpDataItem(CHG_E_SCMDERID, "");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);}

void CHGHandler::bundleMessage()
{
    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);}

void CHGHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(CHG_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(CHG_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(CHG_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(CHG_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(CHG_E_SCMDERID));
}

void CHGHandler::handleCHG()
{
    _exceptionCode = 402;

    this->sendResponseMessage();

}





} } // GreenLeaf::Server

