/*
 * MsgHandlerRepository.h
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

#ifndef MSGHANDLERREPOSITORY_H
#define MSGHANDLERREPOSITORY_H

#include <string>
#include <map>

namespace GreenLeaf {
namespace GLNetIO {

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

    HandlerMap handlers;

};

} } // GreenLeaf::GLNetIO

#include "MsgHandlerRepository.ipp"

#endif // MSGHANDLERREPOSITORY_H

