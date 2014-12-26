/**
 * @file GLNetIO.h
 * @brief GLNetIO库的声明文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef GLNETIO_H
#define GLNETIO_H

#if defined(__WIN32__)
    #if defined(GLNETIO_LIBRARY)
    #  define GLNETIO_SHARED_EXPORT __declspec(dllexport)
    #else
    #  define GLNETIO_SHARED_EXPORT __declspec(dllimport)
    #endif
#else
    #define GLNETIO_SHARED_EXPORT
#endif

#include "GreenLeaf/GLNetIO/TcpConnection.h"
#include "GreenLeaf/GLNetIO/MessageProtocol.h"
#include "GreenLeaf/GLNetIO/MsgHandlerRepository.h"

namespace GreenLeaf {
namespace GLNetIO {

class TcpAcceptor;

/**
 * @brief NetIO库的接口类
 */
class GLNETIO_SHARED_EXPORT NetIO: private boost::noncopyable
{
public:
    /** NetIO的单例接口 */
    static NetIO& instance();

    /** 监听tcp */
    void tcpAcceptor(const unsigned short& port,
            boost::function<void(boost::shared_ptr<TcpConnection>)> operation =
                    boost::function<void(boost::shared_ptr<TcpConnection>)>());

    /** 获取一条连接 */
    TcpConnectionPtr connection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);

    /** 添加一条连接 */
    void addConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);

    /** 删除一条连接 */
    void removeConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);

    /** 更改一条连接 */
    void modifyConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);

    /** 获取在线连接数 */
    const std::string connectionNumber();

    /** 获取单个用户的连接数 */
    const std::string singalUserConnectionNumber(const std::string& userID);

private:
    explicit NetIO();
    virtual ~NetIO();

    boost::shared_ptr<TcpAcceptor> _acceptor;    /**< 监听依赖所需对象 */

};


} } // GreenLeaf::GLNetIO

#endif // GLNETIO_H

