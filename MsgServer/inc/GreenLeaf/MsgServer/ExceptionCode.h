/*
 * ErrorCode.h
 *
 *  Created on: Nov 13, 2014
 *      Author: wim
 */

#ifndef ERRORCODE_H
#define ERRORCODE_H

//#define     DOC_BOOTTYPE_GLOBAL     (1) // ÆóÒµÈ«ŸÖDoc
//#define     DOC_BOOTTYPE_PROJECT    (2) // ÏîÄ¿ÎÄµµ
//#define     DOC_BOOTTYPE_PONSION    (3) // žöÈËÎÄµµ
//#define     DOC_BOOTTYPE_SHARE      (4) // žöÈË¹²Ïí
//
//#define     DC_CLASSID_FILE         (100)
//#define     DC_CLASSID_FOLDER       (101)
//#define     DC_CLASSID_ROOT         (102)
//#define     DC_CLASSID_VFOLDER      (105)
//
//#define     ANT_DOC_ACE_READ            (1) // ÎÄµµµÄReadÈš
//#define     ANT_DOC_ACE_WRITE           (2) // ÎÄµµµÄWriteÈš
//#define     ANT_DOC_ACE_OWNER           (4) // ËùÊôÈš(Èç¹ûÊÇ Root , ÔòËµÃ÷Õâžö Root ÊÇžöÈËRoot )
//#define     ANT_DOC_ACE_MANAGER         (8) // ¹ÜÀíÈš
//
//// ÓÃ»§µÄTalk×ŽÌ¬
//#define     ANT_TALKSTATUS_NONE         (0) // ³õÊŒµÈŽýÓŠŽðµÄ×ŽÌ¬
//#define     ANT_TALKSTATUS_JOIN         (1) // ²ÎÓë»áÒéµÄ
//#define     ANT_TALKSTATUS_REFUSE       (2) // ŸÜŸø»áÒéµÄ
//#define     ANT_TALKSTATUS_AWAY         (3) // Àë¿ª»áÒéµÄ
//
//#define     MANAGER_FOLDER_ROOT         ( 0 )       // Ìž»°ŒÇÂŒ
//#define     MANAGER_FOLDER_BOX_IN       ( 1 )       // ÊÕŒþÏä
//#define     MANAGER_FOLDER_BOX_OUT      ( 2 )       // ·¢ŒþÏä
//#define     MANAGER_FOLDER_FAVORITE     ( 3 )       // ÊÕ²ØŒÐ
//#define     MANAGER_FOLDER_PRE_PROCESS  ( 4 )       // ŽýŽŠÀí
//#define     MANAGER_FOLDER_BOX_DRAFT    ( 5 )       // ²ÝžåÏä
//#define     MANAGER_FOLDER_RECYCLER     ( 6 )       // ÒÑÉŸ³ý
//#define     MANAGER_FOLDER_TALKING      ( 7 )       // »áÒéŒÇÂŒ
//
//// ¶šÒå AntSpace CAddin Flag
//// ¶šÒå AntSpace CAddin Site
//// ¶šÒå AntSpace VAddin Flag
//// ¶šÒå AntSpace VAddin Site
//
//#define ATTACH_FLAG_OWNER_TOUSERPIC         (4)     // ÉèÖÃÎªÓÃ»§µÄPicture
//#define ATTACH_FLAG_OWNER_WEBROOT           (8)     // WebRoot ÏÂµÄÎÄŒþ
//#define ATTACH_FLAG_OWNER_ADS_ID            (16)    // Doc Server µÄžœŒþ
//#define ATTACH_FLAG_OWNER_MSG               (32)    // Message µÄ Attachment
//#define ATTACH_FLAG_OWNER_TALK              (64)    // Talk µÄ Attachment
//#define ATTACH_FLAG_OWNER_TALKMSG           (128)   // Talk ÖÐ Message µÄ Attachment
//#define ATTACH_FLAG_OWNER_ADDIN             (256)   // AddIn µÄ Attachment
//#define ATTACH_FLAG_AUTOVIEW                (512)   // ÔÚœøÐÐ»áÒéÊ±£¬×Ô¶¯ä¯ÀÀ
//#define ATTACH_FLAG_HAVESOURCE              (1024)  // ÊÇ×ª·¢µÄžœŒþ
//#define ATTACH_FLAG_SWARAJ                  (2048)  // ¶ÀÁ¢·¢ËÍžœŒþ
//
//#define ATTACH_OPTION_TRANOPTION_SHOWDLG        (1 )    // ÏÔÊŸœø¶È¶Ô»°¿ò
//#define ATTACH_OPTION_TRANOPTION_REPORT         (2 )    // ±šžæœø¶ÈÐÅÏ¢
//#define ATTACH_OPTION_TRANOPTION_REPORT_MSG     (4 )    // ±šžæœø¶ÈÐÅÏ¢
//#define ATTACH_OPTION_TRANOPTION_OPEN           (8 )    // ÏÂÔØÍêºóŽò¿ªÎÄŒþ£¬Èç¹ûµ±Ç°ÏÂÔØµÄÊÇÄ¿ÂŒ£¬ÔòŽò¿ªÄ¿ÂŒ
//#define ATTACH_OPTION_TRANOPTION_OPENFOLDER     (16 )   // ÏÂÔØÍêºóŽò¿ªÎÄŒþËùÔÚµÄÎÄŒþŒÐ
//
//#define     SHELLEXESTYPE_NORMAL            ( 0 )           // Ä¬ÈÏ
//#define     SHELLEXESTYLE_IEEMPTYBAR        ( 1 )
//
//#define ANT_STYLE_OULOGIN               (1)     //¿ÉÒÔÒÔÆäËüÓÃ»§µÇÂŒ
//#define ANT_STYLE_AUTOPRSMSG            (2)     //¿ÉÒÔ×Ô¶¯ŽŠÀíÒÔÏÂmsg( 1.ÒÑÏÂÔØ 2.UserChat ... )
//#define ANT_STYLE_AUTODWNMSG            (4)     //¿ÉÒÔ×Ô¶¯ÏÂÔØmsg
//#define ANT_STYLE_SHOWAMGER             (8)     //ÏÔÊŸAMSGERœçÃæ
//#define ANT_STYLE_EXITAPP               (16)    //ÏÔÊŸÍË³ö
//#define ANT_STYLE_RELOGIN               (32)    //ÏÔÊŸÖØÐÂLogin
//#define ANT_STYLE_ALLMSGCALLBACK        (64)    //ËùÓÐÏûÏ¢¶ŒÒª CallBack
//#define ANT_STYLE_SHOWVIEWBAR           (128)   // ÏÔÊŸBAR
//#define ANT_STYLE_CANTSETING            ( 256 ) // Òþº¬ÉèÖÃµÄ°ŽÅ¥
//#define ANT_STYLE_DEFAULT   ANT_STYLE_OULOGIN | ANT_STYLE_AUTOPRSMSG
//
//#define ATDB_DATATYPE_INTEGER           (4)
//#define ATDB_DATATYPE_DBTIME            (24)
//#define ATDB_DATATYPE_CHAR              (27)
//
//#define MSG_SHOWMODE_AUTO           (0)
//#define MSG_SHOWMODE_XXX            (1)
//#define MSG_SHOWMODE_CHAT           (2)
//#define MSG_SHOWMODE_MSG            (4)
//#define MSG_SHOWMODE_BROADCAST      (8)
//#define MSG_SHOWMODE_READ_HTML      (16)
//#define MSG_SHOWMODE_WEB            (32)
//
//#define MSG_READSTATE_NONE          (0)
//#define MSG_READSTATE_DOWNLOAD      (1)     // ÒÑÏÂÔØ
//#define MSG_READSTATE_IOPEN         (2)     // ÎÒÒÑŽò¿ª
//#define MSG_READSTATE_LITTLE        (4)     // ²¿·ÖœÓÊÕÕßÒÑŽò¿ª
//#define MSG_READSTATE_ALL           (8)     // ËùÓÐœÓÊÕÕßÒÑŽò¿ª
//#define MSG_READSTATE_ERROR         (16)    // Žò¿ª³öŽí
//
//#define     MEETING_FLAG_NONE           (0)
//#define     MEETING_FLAG_JOINCHECK      (1)         // ŒÓÈëŒì²â
//#define     MEETING_FLAG_OVER_BYOWNER   (2)         // ·¢ÆðÕßÀë¿ªÔòœáÊø
//#define     MEETING_FLAG_FOR_LONG       (4)         // ³€»áÒé
//
//#define     NTY_USERSTATUS_FLAG_ONLINED     (1) // ÒÑŸ­ÔÚÏß
//#define     NTY_USERSTATUS_FLAG_PASSIVE     (2) // ±»¶¯ÍšÖª
//
//
//#define READMSG_FLAG_OWNER_MSG          (1)     // Ä¬ÈÏ Owner , ÊÇÒ»žöÏûÏ¢µÄ Attach
//#define READMSG_FLAG_OWNER_MEET         (2)     // Meet µÄ Attach
//#define READMSG_FLAG_OWNER_MEETMSG      (4)     // Meet ÖÐ Msg µÄ Attach
//#define READMSG_FLAG_OWNER_ADDIN        (8)     // AddIn µÄ Attach
//
////Proxytypes
//#define     PROXYTYPE_NOPROXY   0
//#define     PROXYTYPE_SOCKS4    1
//#define     PROXYTYPE_SOCKS4A   2
//#define     PROXYTYPE_SOCKS5    3
//#define     PROXYTYPE_HTTP11    4
//
////-------------------------------------------------
//// Error Code Define
#define     ERROR_NONE                  ( 0 )       //Ã»ÓÐŽíÎó
//#define     ERR_UNKNOWN                 ( 2 )
//#define     ERR_CMD_CANCELED            ( 3 )       // ÃüÁî±»È¡Ïû
//#define     FILE_IO_ERR                 ( 4 )       // ÎÄŒþ IO ³öŽí
//#define     ERR_XML                     ( 5 )       // XML žñÊœ³öŽí
//#define     ERR_RUNSQL                  ( 6 )       // ÖŽÐÐ SQL ³öŽí
//#define     ERR_RUNCMD                  ( 7 )       // ÖŽÐÐÒ»žöÖžÁî³öŽí
//#define     ERR_CANT_CONNET             ( 8 )       // Á¬œÓ³öŽí
//#define     FILE_CREATE_ERROR           ( 9 )       // ŽŽœšÎÄŒþ³öŽí
//#define     FILE_NOSPACE                ( 10 )      // Ã»ÓÐŽÅÅÌ¿ÕŒä
#define     ERR_CONNECTDB               ( 11 )      // Á¬œÓÊýŸÝ¿â
//#define     ERR_NO_SN                   ( 12 )      // Ã»ÓÐÐòÁÐºÅ
//#define     ERR_CONNCET_CLOSE           ( 13 )
//#define     ERR_NO_USER                 ( 14 )      // Ã»ÓÐÕËºÅ
//#define     ERR_INVALID_FILEINFO        ( 15 )      // ÎÞÐ§µÄÎÄŒþÐÅÏ¢
//#define     ERR_OPEN_DATABASE           ( 16 )      // ²»ÄÜŽò¿ªÊýŸÝ¿â
//#define     ERR_OPEN_REG                ( 17 )      // Žò¿ª×¢²á±í
//
//#define     ERR_DISABLE_SERVICE         ( 200 )     // ·þÎñ±»œû
//#define     ERR_INVALID_PARAM           ( 201 )     // ÎÞÐ§µÄÂ·Ÿ¶
//#define     ERR_INVALID_MSGID           ( 203 )     // ÎÞÐ§µÄÏûÏ¢
//#define     ERR_DOUBLE_REQUEST          ( 204 )
#define     ERR_INVALID_USER            ( 205 )     // ÎÞÐ§µÄÕËºÅ
//#define     ERR_DOMAIN_MISS             ( 206 )
//#define     ERR_INVALID_MSG             ( 207 )
#define     ERR_INVALID_PSW             ( 208 )     // password ³öŽí
//#define     ERR_INVALID_CONNECT         ( 209 )     // ÎÞÐ§µÄÁ¬œÓ
//#define     ERR_IVNALID_GROUP           ( 211 )
//#define     ERR_IVNALID_VIEW            ( 212 )
//#define     ERR_CANT_CREATEDYNAME       ( 213 )
//#define     ERR_USER_LOGINED            ( 215 )     // ÕËºÅÒÑµÇÂŒ
//#define     ERR_USER_ONLIST             ( 216 )
//#define     ERR_USER_OFFLINE            ( 217 )     // ÓÃ»§²»ÔÚÏß
#define     ERR_INVALID_CMD             ( 220 )     // ÎÞÐ§µÄÖžÁî
#define     ERR_INVALID_SESSIONID       ( 221 )     // ÎÞÐ§µÄ»á»°
//#define     ERR_CMD_NOTEXIST            ( 222 )     // ÎÞÐ§µÄÖžÁî
#define     ERR_LOGOUT_OTHERCMPLOGIN    ( 223 )     // ÓÃ»§ÔÚÆäËü»úÆ÷µÇÂŒ
//#define     ERR_LOGOUT_KICK             ( 224 )     // ÓÃ»§±»Ìß³ý
#define     ERR_INVALID_MAC             ( 225 )     // ÎÞÐ§µÄMac
//#define     ERR_UNSUPPORT_VER           ( 226 )     // °æ±ŸÌ«ÀÏ²»Ö§³Ö
//#define     ERR_NOLOGINED               ( 302 )     // ÓÃ»§Ã»µÇÂŒ
//#define     ERR_NOLICENSE               ( 303 )     // Ðí¿ÉÊý³öŽí
#define     ERR_USER_ONLINED            ( 304 )     // ÓÃ»§ÒÑÔÚÏß
//#define     ERR_WEB_GETFPATH            ( 305 )     // žùŸÝURL µÃµœÕæÊµµÄÂ·Ÿ¶
//#define     ERR_OLD_PASSWORD            ( 400 )     // ŸÉÃÜÂë³öŽí
//#define     ERR_FAR_SERVER_DOWN         ( 401 )
#define     ERR_FAR_SERVER_NOTSUPPORT   ( 402 )
//#define     ERR_INVALID_RECEIVER        ( 403 )
//#define     ERR_FILE_NOTFOUND           ( 404 )     // ÎÄŒþÃ»ÕÒµœ
//#define     ERR_INVALID_JOINVALIDATEMAC ( 405 )
//#define     ERR_SERVER_NOT_SUPPORT      ( 407 )     // ²»Ö§³ÖµÄ·þÎñ
//#define     ERR_SERVER_INTERNAL         ( 500 )
//#define     ERR_SERVER_DATABASE         ( 501 )
//#define     ERR_CREATE_MSGFILE          ( 502 )     // ŽŽœšÏûÏ¢žœŒþ³öŽí
//#define     ERR_FILE_OPERATOR           ( 510 )
//#define     ERR_MEMORY_ALLOC            ( 520 )     // ÉêÇëÄÚŽæ³öŽí
//#define     ERR_WRITE_BLOCKING          ( 711 )
#define     ERR_ACCESS_DENIED           ( 912 )
//#define     ERR_SENDMSG_DESABLE         ( 925 )
//#define     ERR_LISTVIEW_DATAERROR      ( 926 )
//#define     ERR_NOSESSION               ( 927 )     // Ã»ÓÐÕÒµœ»á»°


#endif // ERRORCODE_H

