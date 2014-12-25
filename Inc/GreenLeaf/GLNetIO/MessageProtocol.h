/*
 * MessageBuffer.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
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

enum RequestState {
    REQ_NONE = 0,
    REQ_CMDLINE,
    REQ_PARAM,
    REQ_PROP,
    REQ_BODY,
    REQ_DONE,
    REQ_ERROR
};

enum BufferSize {
    BS_BUFFERSIZE = 4096
};

struct MessageBuffer
{
    char _data[BS_BUFFERSIZE + 1];
};
typedef boost::shared_ptr<MessageBuffer> MessageBufferPtr;

struct RequestBuffer
{
    std::size_t _reqStatus;
    std::string _methon;
    ParamsVector _params;
    PropMap _props;
    std::string _body;

    PropKeyVector _enPropKeys;
    PropValueVector _enPropValues;

    boost::shared_ptr<TcpConnection> _conn;
};
typedef boost::shared_ptr<RequestBuffer> RequestBufferPtr;
typedef boost::function<void(RequestBufferPtr)> RequestHandler;

struct ResponseBuffer
{
    std::string _methon;
    ParamsVector _params;
    PropMap _props;
    std::string _body;

    boost::shared_ptr<TcpConnection> _conn;
};
typedef boost::shared_ptr<ResponseBuffer> ResponseBufferPtr;


} } // GreenLeaf::GLNetIO

#endif // MESSAGEBUFFER_H

