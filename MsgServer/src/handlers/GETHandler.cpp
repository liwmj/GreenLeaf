/*
 * GETHandler.cpp
 *
 *  Created on: Nov 25, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/GETDefines.h"
#include "GreenLeaf/MsgServer/handlers/GETHandler.h"

namespace GreenLeaf {
namespace Server {

GETHandler::GETHandler(): HandlerCommon()
{
}

void GETHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(GET_RQ_METHON, msg->_methon);
    this->setTmpDataItem(GET_RQ_FILEPATH, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(GET_RQ_HTTPVER, this->paramItem(msg->_params, 1));
    this->setTmpDataItem(GET_RQ_USERAGENT, this->propValue(msg->_props, "user-agent"));
    this->setTmpDataItem(GET_RQ_HOST, this->propValue(msg->_props, "host"));
    this->setTmpDataItem(GET_RQ_CACHECONTROL, this->propValue(msg->_props, "cachecontrol"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus != GLNetIO::REQ_DONE) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleGET();
    }
}

void GETHandler::operationNormal()
{
    this->bundleMessage();

    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void GETHandler::operationException()
{
}

void GETHandler::bundleMessage()
{
    this->setMethon(_responseBuffer->_methon, "GET");
    this->setParamItem(_responseBuffer->_params, "123123123");
    this->setParamItem(_responseBuffer->_params, "1231564564");
    this->setParamItem(_responseBuffer->_params, "456456456");
    this->setParamItem(_responseBuffer->_params, "909090");
    this->setParamItem(_responseBuffer->_params, "78678678");
    this->setParamItem(_responseBuffer->_params, "123123123");
    this->setParamItem(_responseBuffer->_params, "565");

}

void GETHandler::bundleErrorMessage()
{
}

void GETHandler::handleGET()
{
    this->sendResponseMessage();
}

} } // GreenLeaf::Server

