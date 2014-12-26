/**
 * @file GLNetIO.cpp
 * @brief 网络IO的实现文件
 * @author Wim
 * @version v1.0
 * @date 2014-12-26
 */
#include <iostream>
#include <boost/shared_ptr.hpp>

#include "GreenLeaf/GLUtils.h"

#include "GreenLeaf/GLNetIO/SessionManager.h"
#include "GreenLeaf/GLNetIO/TcpAcceptor.h"
#include "GreenLeaf/GLNetIO.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 创建NetIO的单例对象
 * @return 返回NetIO对象
 */
NetIO& NetIO::instance()
{
    static NetIO _gInstance;
    return _gInstance;
}

/**
 * @brief 初始化NetIO对象
 * @param _acceptor
 */
NetIO::NetIO(): _acceptor()
{
}

/**
 * @brief 析构NetIO
 */
NetIO::~NetIO()
{
}

/**
 * @brief 监听TCP连接
 * @param port 监听端口
 * @param operation 指定回调函数指针
 */
void NetIO::tcpAcceptor(const unsigned short& port,
        boost::function<void(boost::shared_ptr<TcpConnection>)> operation)
{
    _acceptor.reset(new TcpAcceptor(GLUtils::Utils::instance().ioService(), port, operation));
}

/**
 * @brief 获取一条连接
 * @param userID 用户的唯一标示
 * @param sessionID session的ID
 * @param connectionType 连接类型
 * @return 返回连接的指针
 */
TcpConnectionPtr NetIO::connection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType)
{
    return SessionManager::instance().connection(userID, sessionID, connectionType);
}

/**
 * @brief 添加一条连接以及相应的连接管理和Session
 * @param userID 用户的唯一标示
 * @param sessionID session的ID
 * @param connectionType 连接类型
 * @param conn 指定连接的指针
 */
void NetIO::addConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    return SessionManager::instance().addConnection(userID, sessionID, connectionType, conn);
}

/**
 * @brief 删除一条连接以及相应的连接管理和Session
 * @param userID 用户的唯一标示
 * @param sessionID session的ID
 * @param connectionType 连接类型
 */
void NetIO::removeConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType)
{
    return SessionManager::instance().removeConnection(userID, sessionID, connectionType);
}

/**
 * @brief 更改一条连接以及相应的连接管理和Session
 * @param userID 用户的唯一标示
 * @param sessionID session的ID
 * @param connectionType 连接类型
 * @param conn 指定连接
 */
void NetIO::modifyConnection(const std::string& userID,
        const std::string& sessionID,
        const std::string& connectionType,
        const TcpConnectionPtr conn)
{
    return SessionManager::instance().modifyConnection(userID, sessionID, connectionType, conn);
}

/**
 * @brief 获取在线的连接数
 * @return 返回在线连接数
 */
const std::string NetIO::connectionNumber()
{
    return SessionManager::instance().connectionNumber();
}

/**
 * @brief 获取单个用户的连接数
 * @param userID 用户的唯一标示
 * @return 返回单个用户的连接数
 */
const std::string NetIO::singalUserConnectionNumber(const std::string& userID)
{
    return SessionManager::instance().singalUserConnectionNumber(userID);
}

} } // GreenLeaf::GLNetIO

