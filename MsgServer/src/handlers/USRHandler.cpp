/*
 * USRHandler.cpp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#include "GreenLeaf/MsgServer/handlers/USRDefines.h"
#include "GreenLeaf/MsgServer/handlers/USRHandler.h"

namespace GreenLeaf {
namespace Server {

USRHandler::USRHandler(): HandlerCommon()
{
}

void USRHandler::handleMessage(GLNetIO::RequestBufferPtr msg)
{
    this->setTmpDataItem(USR_RQ_METHON, msg->_methon);
    this->setTmpDataItem(USR_RQ_LOGINTYPE, this->paramItem(msg->_params, 0));
    this->setTmpDataItem(USR_RQ_CRYPTTYPE, this->paramItem(msg->_params, 1));
    this->setTmpDataItem(USR_RQ_LOGINNAME, this->paramItem(msg->_params, 2));
    this->setTmpDataItem(USR_RQ_PASSWD, this->paramItem(msg->_params, 3));
    this->setTmpDataItem(USR_RQ_AENFLAG, this->propValue(msg->_props, "aenflag"));
    this->setTmpDataItem(USR_RQ_CLIENTVER, this->propValue(msg->_props, "clientver"));
    this->setTmpDataItem(USR_RQ_CMDID, this->propValue(msg->_props, "cmdid"));
    this->setTmpDataItem(USR_RQ_HOSTNAME, this->propValue(msg->_props, "hostname"));
    this->setTmpDataItem(USR_RQ_LOGINFLAG, this->propValue(msg->_props, "loginflag"));
    this->setTmpDataItem(USR_RQ_MACADDR, this->propValue(msg->_props, "macaddr"));
    this->setTmpDataItem(USR_RQ_PLATFORM, this->propValue(msg->_props, "platform"));
    this->setTmpDataItem(USR_RQ_STATUS, this->propValue(msg->_props, "status"));
    _responseBuffer->_conn = msg->_conn;

    if (msg->_reqStatus == GLNetIO::REQ_ERROR) {
        _exceptionCode = ERR_INVALID_CMD;

    } else {
        this->handleUSR();
    }
}

void USRHandler::operationNormal()
{
    // TODO add value
    this->redundantMsg();
    this->bundleMessage();

    if (_responseBuffer->_conn.get()) {
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
        _netIO.addConnection(this->tmpDataValue(USR_RS_LOGINNAME),
                _sessionType, CONNECTION_TYPE_LOGIN, _responseBuffer->_conn);
    }
}

void USRHandler::operationException()
{
    if (_exceptionCode == ERR_INVALID_USER || _exceptionCode == ERR_INVALID_PSW) {
        this->operationERR();

    } else if (_exceptionCode == ERR_LOGOUT_OTHERCMPLOGIN) {
        this->operationOUT();

    }
}


void USRHandler::bundleMessage()
{
    this->initResponseBufferOperation();

    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(USR_RS_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_ISLOGIN));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_USERID));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_LOGINNAME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_USERNAME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_CONNECTIONID));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_SERVERID));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_LIFETIME));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_SUPERUSER));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_RS_USERLEVEL));
    this->setPropItem(_responseBuffer->_props, "attachsize", this->tmpDataValue(USR_RS_ATTACHSIZE));
    this->setPropItem(_responseBuffer->_props, "autoaway", this->tmpDataValue(USR_RS_AUTOAWAY));
    this->setPropItem(_responseBuffer->_props, "autoawaytime", this->tmpDataValue(USR_RS_AUTOAWAYTIME));
    this->setPropItem(_responseBuffer->_props, "baseace", this->tmpDataValue(USR_RS_BASEACE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(USR_RS_CMDID));
    this->setPropItem(_responseBuffer->_props, "companyname", this->tmpDataValue(USR_RS_COMPANYNAME));
    this->setPropItem(_responseBuffer->_props, "domainname", this->tmpDataValue(USR_RS_DOMAINNAME));
    this->setPropItem(_responseBuffer->_props, "fileserverport", this->tmpDataValue(USR_RS_FILESERVERPORT));
    this->setPropItem(_responseBuffer->_props, "inviews", this->tmpDataValue(USR_RS_INVIEWS));
    this->setPropItem(_responseBuffer->_props, "itemindex", this->tmpDataValue(USR_RS_ITEMINDEX));
    this->setPropItem(_responseBuffer->_props, "leaveday", this->tmpDataValue(USR_RS_LEAVEDAY));
    this->setPropItem(_responseBuffer->_props, "limitrate", this->tmpDataValue(USR_RS_LIMITRATE));
    this->setPropItem(_responseBuffer->_props, "msends", this->tmpDataValue(USR_RS_MSENDS));
    this->setPropItem(_responseBuffer->_props, "msms", this->tmpDataValue(USR_RS_MSMS));
    this->setPropItem(_responseBuffer->_props, "mspagecount", this->tmpDataValue(USR_RS_MSPAGECOUNT));
    this->setPropItem(_responseBuffer->_props, "msppt", this->tmpDataValue(USR_RS_MSPPT));
    this->setPropItem(_responseBuffer->_props, "msppturl", this->tmpDataValue(USR_RS_MSPPTURL));
    this->setPropItem(_responseBuffer->_props, "msrs", this->tmpDataValue(USR_RS_MSRS));
    this->setPropItem(_responseBuffer->_props, "pic", this->tmpDataValue(USR_RS_PIC));
    this->setPropItem(_responseBuffer->_props, "roleids", this->tmpDataValue(USR_RS_ROLEIDS));
    this->setPropItem(_responseBuffer->_props, "scmderid",this->tmpDataValue(USR_RS_SCMDERID));
    this->setPropItem(_responseBuffer->_props, "serverflag", this->tmpDataValue(USR_RS_SERVERFLAG));
    this->setPropItem(_responseBuffer->_props, "servertime", this->tmpDataValue(USR_RS_SERVERTIME));
    this->setPropItem(_responseBuffer->_props, "stosAce", this->tmpDataValue(USR_RS_STOSACE));
    this->setPropItem(_responseBuffer->_props, "token", this->tmpDataValue(USR_RS_TOKEN));
    this->setPropItem(_responseBuffer->_props, "vertype", this->tmpDataValue(USR_RS_VERTYPE));
}

void USRHandler::bundleErrorMessage()
{
    this->initResponseBufferOperation();
    this->setMethon(_responseBuffer->_methon, this->tmpDataValue(USR_E_METHON));
    this->setParamItem(_responseBuffer->_params, this->tmpDataValue(USR_E_ERRORCODE));
    this->setPropItem(_responseBuffer->_props, "cmdid", this->tmpDataValue(USR_E_CMDID));
    this->setPropItem(_responseBuffer->_props, "methon", this->tmpDataValue(USR_E_CMDNAME));
    this->setPropItem(_responseBuffer->_props, "scmderid", this->tmpDataValue(USR_E_SCMDERID));
}

void USRHandler::handleUSR()
{
    std::string loginType = this->tmpDataValue(USR_RQ_LOGINTYPE);
    if (loginType == "L") {
        this->handleUSR_L();

    } else if (loginType == "R") {
        this->handleUSR_R();

    } else {
        _exceptionCode = ERR_INVALID_CMD;
        this->sendResponseMessage();
    }
}

void USRHandler::handleUSR_L()
{
    if (!this->verifyUser()) {
        std::cout << "verify user error" << std::endl;
        _exceptionCode = ERR_INVALID_USER;
        return ;
    } else {
        this->setTmpDataItem(USR_RS_ISLOGIN, "OK");
        this->setTmpDataItem(USR_RS_LOGINNAME, _dataCache->_loginName + "@aipu.com");
        this->userType();
    }

    if (!this->verifyPasswd()) {
        std::cout << "verify passwd error" << std::endl;
        _exceptionCode = ERR_INVALID_PSW;
        return ;
    } else {
        // TODO
        this->setTmpDataItem(USR_RS_ISLOGIN, "OK");

    }

    if (this->isKillUser()) {
        std::cout << "kill user" << std::endl;
        _exceptionCode = ERR_LOGOUT_OTHERCMPLOGIN;
        return ;
    }



//    bool isValidate = false;
//    if(userType == USER_TYPE_GUEST_WEB) {
//        isValidate = true;
//    } else{
//        isValidate = this->checkPasswd(loginName, passwd, cryptType);
//    }
//
//
//    if(userType == USER_TYPE_GUEST || userType == USER_TYPE_GUEST_WEB) {
//        m_strStuffLoginName = m_strLoginName;
//        GetNewUserName( pRequest, m_strLoginName, m_strUserName );
//    }

}

void USRHandler::handleUSR_R()
{
    _exceptionCode = ERR_INVALID_SESSIONID;
}

void USRHandler::operationERR()
{
    this->setTmpDataItem(USR_E_METHON, "ERR");
    this->setTmpDataItem(USR_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(USR_E_CMDID, this->tmpDataValue(USR_RQ_CMDID));
    this->setTmpDataItem(USR_E_CMDNAME, this->tmpDataValue(USR_RQ_METHON));
//        this->setTmpDataItem(USR_E_SCMDERID, this->tmpDataValue(USR_RQ_SCMDERID));
    this->bundleErrorMessage();
    if (_responseBuffer->_conn.get())
        _responseBuffer->_conn->sendBundleMessage(_responseBuffer);
}

void USRHandler::operationOUT()
{
    this->setTmpDataItem(USR_E_METHON, "OUT");
    this->setTmpDataItem(USR_E_ERRORCODE, boost::lexical_cast<std::string>(_exceptionCode));
    this->setTmpDataItem(USR_E_CMDID, this->tmpDataValue(USR_RQ_CMDID));
    this->setTmpDataItem(USR_E_CMDNAME, this->tmpDataValue(USR_RQ_METHON));
//        this->setTmpDataItem(USR_E_SCMDERID, this->tmpDataValue(USR_RQ_SCMDERID));

    this->bundleErrorMessage();
    if (_netIO.connection(this->tmpDataValue(USR_RS_LOGINNAME),
            _sessionType, CONNECTION_TYPE_LOGIN)) {
        _netIO.connection(this->tmpDataValue(USR_RS_LOGINNAME),
                _sessionType, CONNECTION_TYPE_LOGIN)->sendBundleMessage(_responseBuffer);
        _netIO.removeConnection(this->tmpDataValue(USR_RS_LOGINNAME),
                _sessionType, CONNECTION_TYPE_LOGIN);
    }

    this->operationNormal();
}

const bool USRHandler::verifyUser()
{
    std::string loginName = this->tmpDataValue(USR_RQ_LOGINNAME);

    _dataCache = _userManager.dataCache(loginName);
    if (_dataCache->_name.empty()) {
        if (!this->updateCacheData(loginName)) {
            return false;
        }
    }
    return true;
}

const bool USRHandler::verifyPasswd()
{
    std::string loginName = this->tmpDataValue(USR_RQ_LOGINNAME);
    std::string passwd = this->tmpDataValue(USR_RQ_PASSWD);
    std::string cryptType = this->tmpDataValue(USR_RQ_CRYPTTYPE);

    if (cryptType == "ATEN") {

        std::string str("000000");
        _utils.md5Encrypt(str);
//        std::cout << "passwd ----------------  " << str << std::endl;
//        std::string str("e10adc3949ba59abbe56e057f20f883e");
//        _utils.atenDecrypt(str, PSW_KEY);
//        std::cout << "passwd ----------------  " << passwd << "   " << str << std::endl;
    } else if (cryptType == "MD5") {

    } else if (cryptType == "MD5EX") {

    } else if (cryptType == "NON"){

    } else {
        return false;
    }


    return true;
}

const bool USRHandler::isKillUser()
{
    switch (std::atoi(this->tmpDataValue(USR_RQ_PLATFORM).c_str())) {
    case ANT_CLIENT_WIN:
        _sessionType = SESSION_TYPE_WIN;
        break;
    case ANT_CLIENT_WEB:
        _sessionType = SESSION_TYPE_WEB;
        break;
    case ANT_CLIENT_ANDROID:
        _sessionType = SESSION_TYPE_ANDROID;
        break;
    case ANT_CLIENT_MAC:
        _sessionType = SESSION_TYPE_MAC;
        break;
    case ANT_CLIENT_IOS:
        _sessionType = SESSION_TYPE_IOS;
        break;
    default:
        break;
    }

    if (_netIO.connection(this->tmpDataValue(USR_RS_LOGINNAME),
            _sessionType, CONNECTION_TYPE_LOGIN)) {
        return true;
    }
    return false;
}

void USRHandler::userType()
{
    std::string loginName = this->tmpDataValue(USR_RQ_LOGINNAME);
    std::transform(loginName.begin(), loginName.end(), loginName.begin(), ::tolower);
    _userType = USER_TYPE_UNKNOWN;
    if (!loginName.empty()) {
        if (loginName.compare(USER_TYPE_GUEST_WEB) == 0) {
            _userType = USER_TYPE_GUEST_WEB;
        } else if (loginName.find(USER_TYPE_GUEST) == 0 ) {
            _userType = USER_TYPE_GUEST;
        } else if (loginName.find(USER_TYPE_SYSTEM)) {
            _userType = USER_TYPE_SYSTEM;
        } else {
            _userType = USER_TYPE_NONE;
        }
    }
}

const bool USRHandler::updateCacheData(const std::string& loginName)
{
    bool isExistUser = false;
    std::vector<std::string> vecRes;
    std::string query = boost::str(boost::format("\
            SELECT col_ID, col_LoginName, col_Name, col_PWord, col_EnType, col_ItemIndex, col_Note, Col_FarServer, Col_IpAddr \
            FROM hs_User \
            WHERE col_LoginName = '%s' \
            AND col_Disabled = 0;") % loginName);

    vecRes = _dbIO.selectData(GLDBIO::DT_MYSQL, query);
    if (vecRes.empty()) {
        std::cout << "sql res empty" << std::endl;
        return isExistUser = false;
    } else {
        isExistUser = true;
    }
    _dataCache->_id = vecRes.at(0);
    _dataCache->_loginName = vecRes.at(1);
    _dataCache->_name = vecRes.at(2);
    _dataCache->_pword = vecRes.at(3);
    _dataCache->_enType = vecRes.at(4);
    _dataCache->_itemIndex = vecRes.at(5);
    _dataCache->_note = vecRes.at(6);
    _dataCache->_farServer = vecRes.at(7);
    _dataCache->_ipAddr = vecRes.at(8);

    _userManager.setDataCache(loginName, _dataCache);

    return isExistUser;
}

void USRHandler::redundantMsg()
{
    this->setTmpDataItem(USR_RS_METHON, this->tmpDataValue(USR_RQ_METHON));
    this->setTmpDataItem(USR_RS_ISLOGIN, "OK");
    this->setTmpDataItem(USR_RS_USERID, _dataCache->_id);
    this->setTmpDataItem(USR_RS_LOGINNAME, _dataCache->_loginName + "@aipu.com");
    this->setTmpDataItem(USR_RS_USERNAME, _dataCache->_name);
    this->setTmpDataItem(USR_RS_CONNECTIONID, _responseBuffer->_conn->id());
    this->setTmpDataItem(USR_RS_SERVERID, "C9B9A3BE-5000-444F-93FF-713CF1743C05");
    this->setTmpDataItem(USR_RS_LIFETIME, "40000");
    this->setTmpDataItem(USR_RS_SUPERUSER, "0");
    this->setTmpDataItem(USR_RS_USERLEVEL, _dataCache->_itemIndex);
    this->setTmpDataItem(USR_RS_ATTACHSIZE, "-1");
    this->setTmpDataItem(USR_RS_AUTOAWAY, "1");
    this->setTmpDataItem(USR_RS_AUTOAWAYTIME, "10");
    this->setTmpDataItem(USR_RS_BASEACE, "8193");
    this->setTmpDataItem(USR_RS_CMDID, this->tmpDataValue(USR_RQ_CMDID));
    this->setTmpDataItem(USR_RS_COMPANYNAME, "艾朴软件");
    this->setTmpDataItem(USR_RS_DOMAINNAME, "aipu.com");
    this->setTmpDataItem(USR_RS_FILESERVERPORT, "6663");
    this->setTmpDataItem(USR_RS_INVIEWS, "622,996,4245,4458,4524,4580,4584,4586,4624,4713,4761,4762,4811,4821,4828,4829,4843,4847,4850,4868,4869,4873,4898,4899,4900,4901,4902,4903,4904,4905,4906,4907,4908,4913,4914,4915,4916,4917,4918,4920,4926,4927,4944,4990");
    this->setTmpDataItem(USR_RS_ITEMINDEX, _dataCache->_itemIndex);
    this->setTmpDataItem(USR_RS_LEAVEDAY, "-1");
    this->setTmpDataItem(USR_RS_LIMITRATE, "-1");
    this->setTmpDataItem(USR_RS_MSENDS, "-1");
    this->setTmpDataItem(USR_RS_MSMS, "192.168.0.8:36500");
    this->setTmpDataItem(USR_RS_MSPAGECOUNT, "8");
    this->setTmpDataItem(USR_RS_MSPPT, "ShowPlay");
    this->setTmpDataItem(USR_RS_MSPPTURL, "http://meeting.bigant.cn:80/ShowPlay");
    this->setTmpDataItem(USR_RS_MSRS, "192.168.0.8:36501");
//    this->setTmpDataItem(USR_RS_PIC, "AntWeb://Faces\{0DC9F880-A984-465A-A5A2-DAE2CB34B49D}.png");
    this->setTmpDataItem(USR_RS_ROLEIDS, "51,64,65");
    this->setTmpDataItem(USR_RS_SCMDERID, "{7659700D-C607-4F38-9E5C-312F4CC47FE0}");
    this->setTmpDataItem(USR_RS_SERVERFLAG, "458787");
    this->setTmpDataItem(USR_RS_SERVERTIME, "2014-11-24%203:18:19");
    this->setTmpDataItem(USR_RS_STOSACE, "3");
    this->setTmpDataItem(USR_RS_TOKEN, "{F3C3F680-271C-4D2C-B36F-34A69D6E6344}");
    this->setTmpDataItem(USR_RS_VERTYPE, "2");
}


} } // GreenLeaf::Server

