/**
 * @file MessageProtocol.h
 * @brief 消息协议的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include <string>
#include <vector>
#include <map>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

namespace GreenLeaf {
namespace GLNetIO {

typedef std::vector<std::string> ParamsVector;
typedef std::map<std::string, std::string> PropMap;
typedef std::vector<std::string> PropKeyVector;
typedef std::vector<std::string> PropValueVector;

class TcpConnection;

/** 请求状态枚举 */
enum RequestState {
    REQ_NONE = 0,   /**< 默认状态 */
    REQ_CMDLINE,    /**< 解析命令行状态 */
    REQ_PARAM,      /**< 解析参数状态 */
    REQ_PROP,       /**< 解析属性状态 */
    REQ_BODY,       /**< 解析体状态 */
    REQ_DONE,       /**< 解析完成状态 */
    REQ_ERROR       /**< 解析错误 */
};

/** 缓冲区大小 */
enum BufferSize {
    BS_BUFFERSIZE = 4096    /**< 默认大小 */
};

/** 缓冲区 */
struct MessageBuffer
{
    char _data[BS_BUFFERSIZE + 1];  /**< 缓冲区串 */
};
typedef boost::shared_ptr<MessageBuffer> MessageBufferPtr;

/** 请求缓冲区 */
struct RequestBuffer
{
    std::size_t _reqStatus;                 /**< 请求状态 */
    std::string _methon;                    /**< methon数据 */
    ParamsVector _params;                   /**< params数据 */
    PropMap _props;                         /**< props数据 */
    std::string _body;                      /**< body数据 */

    PropKeyVector _enPropKeys;              /**< 加密版prop的键 */
    PropValueVector _enPropValues;          /**< 加密版prop的值 */

    boost::shared_ptr<TcpConnection> _conn; /**< 当前连接的指针 */
};
typedef boost::shared_ptr<RequestBuffer> RequestBufferPtr;
typedef boost::function<void(RequestBufferPtr)> RequestHandler;

/** 应答缓冲区 */
struct ResponseBuffer
{
    std::string _methon;                    /**< methon数据 */
    ParamsVector _params;                   /**< params数据 */
    PropMap _props;                         /**< props数据 */
    std::string _body;                      /**< body数据 */

    boost::shared_ptr<TcpConnection> _conn; /**< 当前连接的指针 */
};
typedef boost::shared_ptr<ResponseBuffer> ResponseBufferPtr;


} } // GreenLeaf::GLNetIO

#endif // MESSAGEBUFFER_H

