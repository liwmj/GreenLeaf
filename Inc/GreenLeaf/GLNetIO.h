/*
 * GLNetIO.h
 *
 *  Created on: Oct 30, 2014
 *      Author: wim
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

class GLNETIO_SHARED_EXPORT NetIO: private boost::noncopyable
{
public:
    static NetIO& instance();
    void tcpAcceptor(const unsigned short& port,
            boost::function<void(boost::shared_ptr<TcpConnection>)> operation =
                    boost::function<void(boost::shared_ptr<TcpConnection>)>());

    TcpConnectionPtr connection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);
    void addConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);
    void removeConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType);
    void modifyConnection(const std::string& userID,
            const std::string& sessionID,
            const std::string& connectionType,
            const TcpConnectionPtr conn);

    const std::string connectionNumber();
    const std::string singalUserConnectionNumber(const std::string& userID);

private:
    explicit NetIO();
    virtual ~NetIO();

    boost::shared_ptr<TcpAcceptor> _acceptor;

};


} } // GreenLeaf::GLNetIO

#endif // GLNETIO_H

