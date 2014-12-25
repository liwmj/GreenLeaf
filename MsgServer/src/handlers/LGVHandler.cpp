/*
 * LGVHandler.cpp
 *
 *  Created on: Dec 2, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/LGVDefines.h"
#include "GreenLeaf/MsgServer/handlers/LGVHandler.h"

namespace GreenLeaf {
namespace Server {

LGVHandler::LGVHandler(): HandlerCommon()
{
}

void LGVHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(LGV_RQ_METHON, msg->_methon);
    this->setTmpDataItem(LGV_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(LGV_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleLGV();
    }
}

void LGVHandler::operationNormal()
{
    this->redundantMsg();



    this->bundleMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LGVHandler::operationException()
{

    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void LGVHandler::bundleMessage()
{
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(LGV_RS_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LGV_RS_GROUPINDEX));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LGV_RS_GROUPCOUNT));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LGV_RS_VIEWID));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LGV_RS_VIEWNAME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(LGV_RS_ITEMINDEX));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(LGV_RS_CMDID));
    this->setPropItem(_responseBuffer->_props, "domainname", this->tmpDataValue(LGV_RS_DOMAINNAME));
    this->setPropItem(_responseBuffer->_props, "ownerid", this->tmpDataValue(LGV_RS_OWNERID));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(LGV_RS_SCMDERID));
}

void LGVHandler::bundleErrorMessage()
{

}

void LGVHandler::handleLGV()
{
    this->sendResponseMessage();
}

void LGVHandler::redundantMsg()
{
    this->setTmpDataItem(LGV_RS_METHON, this->tmpDataValue(LGV_RQ_METHON));
    this->setTmpDataItem(LGV_RS_GROUPINDEX, "0");
    this->setTmpDataItem(LGV_RS_GROUPCOUNT, "0");
    this->setTmpDataItem(LGV_RS_VIEWID, "0");
    this->setTmpDataItem(LGV_RS_VIEWNAME, "0");
    this->setTmpDataItem(LGV_RS_ITEMINDEX, "10000");
    this->setTmpDataItem(LGV_RS_CMDID, this->tmpDataValue(LGV_RQ_CMDID));
    this->setTmpDataItem(LGV_RS_DOMAINNAME, "aipu.com");
    this->setTmpDataItem(LGV_RS_OWNERID, "0");
    this->setTmpDataItem(LGV_RS_SCMDERID, "{6FD99ACF-86EE-4A86-8823-F2162DE63B8A}");
}


} } // GreenLeaf::Server

