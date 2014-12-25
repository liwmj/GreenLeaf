/*
 * LSVHandler.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/LSVDefines.h"
#include "GreenLeaf/MsgServer/handlers/LSVHandler.h"

namespace GreenLeaf {
namespace Server {

LSVHandler::LSVHandler(): HandlerCommon()
{
}

void LSVHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(LSV_RQ_METHON, msg->_methon);
    this->setTmpDataItem(LSV_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(LSV_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    this->setTmpDataItem(LSV_RQ_VIEWTYPES, this->propValue(msg->_props, "viewtypes"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleLSV();
    }
}

void LSVHandler::operationNormal()
{
    this->redundantMsg();





    this->bundleMessage();

    _responseBuffer->_conn->sendBundleMessage(_responseBuffer);

}

void LSVHandler::operationException()
{


    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LSVHandler::bundleMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(LSV_RS_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWINDEX));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWCOUNT));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWTYPE));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWID));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWNAME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_VIEWSTYLE));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LSV_RS_ITEMINDEX));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(LSV_RS_CMDID));
    this->setPropItem(_responseBuffer->_props, "domainname", this->tmpDataValue(LSV_RS_DOMAINNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(LSV_RS_SCMDERID));
}

void LSVHandler::bundleErrorMessage()
{

}

void LSVHandler::handleLSV()
{
    this->sendResponseMessage();
}

void LSVHandler::redundantMsg()
{
    this->setTmpDataItem(LSV_RS_METHON, this->tmpDataValue(LSV_RQ_METHON));
    this->setTmpDataItem(LSV_RS_VIEWINDEX, "1");
    this->setTmpDataItem(LSV_RS_VIEWCOUNT, "1");
    this->setTmpDataItem(LSV_RS_VIEWTYPE, "1");
    this->setTmpDataItem(LSV_RS_VIEWID, "11");
    this->setTmpDataItem(LSV_RS_VIEWNAME, "UP");
    this->setTmpDataItem(LSV_RS_VIEWSTYLE, "0");
    this->setTmpDataItem(LSV_RS_ITEMINDEX, "10000");
    this->setTmpDataItem(LSV_RS_CMDID, this->tmpDataValue(LSV_RQ_CMDID));
    this->setTmpDataItem(LSV_RS_DOMAINNAME, "aipu.com");
    this->setTmpDataItem(LSV_RS_SCMDERID, "{634EAD05-C90A-4459-8FB8-4FCE6F60E261}");
}


} } // GreenLeaf::Server

