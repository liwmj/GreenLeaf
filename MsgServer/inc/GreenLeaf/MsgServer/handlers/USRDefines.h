/*
 * USRDefines.h
 *
 *  Created on: Nov 26, 2014
 *      Author: wim
 */

#ifndef USRDEFINES_H
#define USRDEFINES_H

#define PSW_KEY                         ("2B9i7g1A14n20t")
#define CENTER_PWS_KEY                  ("!@3*(DPOdccd&*")

#define ANT_CLIENT_WIN                  (0)     // PC客户端
#define ANT_CLIENT_WEB                  (1)     // web访问
#define ANT_CLIENT_ANDROID              (2)     // android
#define ANT_CLIENT_MAC                  (3)     // mac客户端
#define ANT_CLIENT_IOS                  (4)     // ios

#define USER_TYPE_UNKNOWN               ("unknown")    //未知用户类型
#define USER_TYPE_NONE                  ("none")     // 一般用户
#define USER_TYPE_GUEST                 ("ant_guest")     // ant_Guest
#define USER_TYPE_SYSTEM                ("ant_system")     // ant_System
#define USER_TYPE_SERVER                ("server")     // 服务端用户
#define USER_TYPE_GUEST_WEB             ("ant_guest_web")     // ant_Guest

//#define LOGINFLAG_NOKICK                (1)     // 不进行踢除
//#define LOGINFLAG_NORCV_USERSTATUS      (2)     // 不接收用户状态通知
//#define LOGINFLAG_NOLICENCE             (4)     // 不占节点数
//#define LOGINFLAG_OPENDB                (8)     // 打开数据库
//#define LOGINFLAG_NOTLOAD_ACSVIEWS      (16)    // 不自动装入当前用户可防问的视图列表
//#define LOGINFLAG_NOTLOAD_USERASVIEWS   (32)    // 不自动装入当前用户所在的视图
//#define LOGINFLAG_MSGFORMAT_ONLY_TEXT   (64)    // 只收发 Text 消息
//#define LOGINFLAG_SUER_STRCMD           (128)   // 使用String 指令(每个指令都以 '\0' 进行结尾)
//#define LOGINFLAG_FROM_FLASH            (256)   // Form Web
//#define LOGINFLAG_NOCHECKPSW            (512)   // 不检测Password
//#define LOGINFLAG_FORM_NOJM             (1024)  // 密码不加密

#define SESSION_TYPE_WIN                ("pc")
#define SESSION_TYPE_WEB                ("web")
#define SESSION_TYPE_ANDROID            ("mobile")
#define SESSION_TYPE_MAC                ("pc")
#define SESSION_TYPE_IOS                ("mobile")

#define CONNECTION_TYPE_LOGIN           ("login")
#define CONNECTION_TYPE_TALK            ("talk")

#define USR_RQ_METHON                   ("USR_RQ_methon")
#define USR_RQ_LOGINTYPE                ("USR_RQ_loginType")
#define USR_RQ_CRYPTTYPE                ("USR_RQ_cryptType")
#define USR_RQ_LOGINNAME                ("USR_RQ_loginName")
#define USR_RQ_PASSWD                   ("USR_RQ_passwd")
#define USR_RQ_AENFLAG                  ("USR_RQ_aenFlag")
#define USR_RQ_CLIENTVER                ("USR_RQ_clientVer")
#define USR_RQ_CMDID                    ("USR_RQ_cmdID")
#define USR_RQ_HOSTNAME                 ("USR_RQ_hostname")
#define USR_RQ_LOGINFLAG                ("USR_RQ_loginFlag")
#define USR_RQ_MACADDR                  ("USR_RQ_macAddr")
#define USR_RQ_PLATFORM                 ("USR_RQ_platform")
#define USR_RQ_STATUS                   ("USR_RQ_status")

#define USR_RS_METHON                   ("USR_RS_methon")
#define USR_RS_ISLOGIN                  ("USR_RS_isLogin")
#define USR_RS_USERID                   ("USR_RS_userID")
#define USR_RS_LOGINNAME                ("USR_RS_loginName")
#define USR_RS_USERNAME                 ("USR_RS_userName")
#define USR_RS_CONNECTIONID             ("USR_RS_connectionID")
#define USR_RS_SERVERID                 ("USR_RS_serverID")
#define USR_RS_LIFETIME                 ("USR_RS_lifeTime")
#define USR_RS_SUPERUSER                ("USR_RS_superUser")
#define USR_RS_USERLEVEL                ("USR_RS_userLevel")
#define USR_RS_ATTACHSIZE               ("USR_RS_attachSize")
#define USR_RS_AUTOAWAY                 ("USR_RS_autoAway")
#define USR_RS_AUTOAWAYTIME             ("USR_RS_autoAwayTime")
#define USR_RS_BASEACE                  ("USR_RS_baseAce")
#define USR_RS_CMDID                    ("USR_RS_cmdID")
#define USR_RS_COMPANYNAME              ("USR_RS_companyName")
#define USR_RS_DOMAINNAME               ("USR_RS_domainName")
#define USR_RS_FILESERVERPORT           ("USR_RS_fileServerPort")
#define USR_RS_INVIEWS                  ("USR_RS_inViews")
#define USR_RS_ITEMINDEX                ("USR_RS_itemIndex")
#define USR_RS_LEAVEDAY                 ("USR_RS_leaveDay")
#define USR_RS_LIMITRATE                ("USR_RS_limitRate")
#define USR_RS_MSENDS                   ("USR_RS_mSends")
#define USR_RS_MSMS                     ("USR_RS_msms")
#define USR_RS_MSPAGECOUNT              ("USR_RS_msPageCount")
#define USR_RS_MSPPT                    ("USR_RS_msPPT")
#define USR_RS_MSPPTURL                 ("USR_RS_msPPTUrl")
#define USR_RS_MSRS                     ("USR_RS_msrs")
#define USR_RS_PIC                      ("USR_RS_pic")
#define USR_RS_ROLEIDS                  ("USR_RS_roleIDs")
#define USR_RS_SCMDERID                 ("USR_RS_scmderID")
#define USR_RS_SERVERFLAG               ("USR_RS_serverFlag")
#define USR_RS_SERVERTIME               ("USR_RS_serverTime")
#define USR_RS_STOSACE                  ("USR_RS_stoSAce")
#define USR_RS_TOKEN                    ("USR_RS_token")
#define USR_RS_VERTYPE                  ("USR_RS_verType")

#define USR_E_METHON                    ("USR_E_err")
#define USR_E_ERRORCODE                 ("USR_E_errorCode")
#define USR_E_CMDID                     ("USR_E_cmdID")
#define USR_E_CMDNAME                   ("USR_E_cmdName")
#define USR_E_SCMDERID                  ("USR_E_scmderID")

#endif // USRDEFINES_H



