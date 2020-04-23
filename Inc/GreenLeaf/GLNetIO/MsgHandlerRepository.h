/**
 * @file MsgHandlerRepository.h
 * @brief 消息处理器仓库的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef MSGHANDLERREPOSITORY_H
#define MSGHANDLERREPOSITORY_H

#include <string>
#include <map>

namespace GreenLeaf {
namespace GLNetIO {

/**
 * @brief 消息处理器仓库类
 * @tparam Handler 具体的操作
 */
template<typename Handler>
class MsgHandlerRepository
{
public:
    static MsgHandlerRepository& instance();

    bool registerHandler(const std::string& code, Handler handler);

    void removeHandler(const std::string& code);

    Handler handler(const std::string& code) const;

private:
    MsgHandlerRepository();
    MsgHandlerRepository(const MsgHandlerRepository& other);
    MsgHandlerRepository& operator=(const MsgHandlerRepository& other);

private:
    typedef std::map<std::string, Handler> HandlerMap;

    HandlerMap handlers;    /**< 存放处理的容器 */

};

} } // GreenLeaf::GLNetIO

#include "MsgHandlerRepository.ipp"

#endif // MSGHANDLERREPOSITORY_H

