/*
 * CUSHandler.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/CUSDefines.h"
#include "GreenLeaf/MsgServer/handlers/CUSHandler.h"

namespace GreenLeaf {
namespace Server {

CUSHandler::CUSHandler(): HandlerCommon()
{
}

void CUSHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(CUS_RQ_METHON, msg->_methon);
    this->setTmpDataItem(CUS_RQ_SERVICENAME, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(CUS_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(CUS_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleCUS();
    }
}

void CUSHandler::operationNormal()
{
    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);}

void CUSHandler::operationException()
{
    this->setTmpDataItem(CUS_E_METHON, "ERR");
    this->setTmpDataItem(CUS_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(CUS_E_CMDID, this->tmpDataValue(CUS_RQ_CMDID));
    this->setTmpDataItem(CUS_E_CMDNAME, this->tmpDataValue(CUS_RQ_METHON));
    this->setTmpDataItem(CUS_E_SCMDERID, "");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);}

void CUSHandler::bundleMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(CUS_RS_METHON));
//    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(CUS_RS_SERVICENAME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(CUS_RS_USERCOUNT));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(CUS_RS_CMDID));
    this->setPropItem(_responseBuffer->_props, "users", this->tmpDataValue(CUS_RS_MAXUSERNUMBER));
}

void CUSHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(CUS_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(CUS_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(CUS_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(CUS_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(CUS_E_SCMDERID));
}

void CUSHandler::handleCUS()
{
    if (this->tmpDataValue(CUS_RQ_SERVICENAME) == "_ALL") {
        this->setTmpDataItem(CUS_RS_METHON, this->tmpDataValue(CUS_RQ_METHON));
//        this->setTmpDataItem(CUS_RS_SERVICENAME, "_ALL");
        this->setTmpDataItem(CUS_RS_USERCOUNT, _netIO.connectionNumber());
        this->setTmpDataItem(CUS_RS_CMDID, this->tmpDataValue(CUS_RQ_CMDID));
        this->setTmpDataItem(CUS_RS_MAXUSERNUMBER, "4096000");

    } else {
        std::cout << this->tmpDataValue(CUS_RQ_SERVICENAME) << std::endl;
    }

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

