/*
 * LCAHandler.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/LCADefines.h"
#include "GreenLeaf/MsgServer/handlers/LCAHandler.h"

namespace GreenLeaf {
namespace Server {

LCAHandler::LCAHandler(): HandlerCommon()
{
}

void LCAHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(LCA_RQ_METHON, msg->_methon);
    this->setTmpDataItem(LCA_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(LCA_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    this->setTmpDataItem(LCA_RQ_ROLEIDS, this->propValue(msg->_props, "roleids"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleLCA();
    }
}

void LCAHandler::operationNormal()
{
    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LCAHandler::operationException()
{
    this->setTmpDataItem(LCA_E_METHON, "ERR");
    this->setTmpDataItem(LCA_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(LCA_E_CMDID, this->tmpDataValue(LCA_RQ_CMDID));
    this->setTmpDataItem(LCA_E_CMDNAME, this->tmpDataValue(LCA_RQ_METHON));
    this->setTmpDataItem(LCA_E_SCMDERID, "{9CB5224E-6A4D-41D6-AAAF-830F4362E0F0}");

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);}

void LCAHandler::bundleMessage()
{

}

void LCAHandler::bundleErrorMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(LCA_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LCA_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(LCA_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(LCA_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(LCA_E_SCMDERID));
}

void LCAHandler::handleLCA()
{
    _exceptionCode = 402;

    this->sendResponseMessage();

}

} } // GreenLeaf::Server

