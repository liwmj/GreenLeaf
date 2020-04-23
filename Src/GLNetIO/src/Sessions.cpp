/**
 * @file Sessions.cpp
 * @brief session集合的实现文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#include "GreenLeaf/GLNetIO/Sessions.h"

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 获取session集合
 * @return 返回session集合
 */
const ConnectionsPtrMap& Sessions::connectionsPtrMap() const
{
    return _connectionsPtrMap;
}

/**
 * @brief 获取一条session
 * @param sessionType session类型
 * @return 返回session的指针
 */
ConnectionsPtr Sessions::session(const std::string sessionType)
{
    ConnectionsPtrMap::iterator it = _connectionsPtrMap.find(sessionType);
    return it == _connectionsPtrMap.end() ? ConnectionsPtr() : it->second;
}

/**
 * @brief 添加一条session
 * @param sessionType session类型
 * @param connections 连接集合
 */
void Sessions::addSession(const std::string sessionType,
        ConnectionsPtr connections)
{
    _connectionsPtrMap.insert(std::make_pair(sessionType, connections));
}

/**
 * @brief 删除一条session
 * @param sessionType session类型
 */
void Sessions::removeSession(const std::string sessionType)
{
    _connectionsPtrMap.erase(sessionType);
}

/**
 * @brief 更改一条session
 * @param sessionType session类型
 * @param connections 连接集合
 */
void Sessions::modifySession(const std::string sessionType,
        ConnectionsPtr connections)
{
    ConnectionsPtrMap::iterator it = _connectionsPtrMap.find(sessionType);
    if (it != _connectionsPtrMap.end()) {
        it->second.reset();
        it->second = connections;
    }
}

} } // GreenLeaf::GLNetIO

