/*
 * MsgHandlerRepository.ipp
 *
 *  Created on: Nov 12, 2014
 *      Author: wim
 */

namespace GreenLeaf {
namespace GLNetIO {

template<typename Handler>
MsgHandlerRepository<Handler>& MsgHandlerRepository<Handler>::instance()
{
    static MsgHandlerRepository<Handler> _gInstance;
    return _gInstance;
}

template<typename Handler>
bool MsgHandlerRepository<Handler>::registerHandler(const std::string& code,
        Handler handler) {
    return this->handlers.insert(std::make_pair(code, handler)).second;
}

template<typename Handler>
void MsgHandlerRepository<Handler>::removeHandler(const std::string& code)
{
    this->handlers.erase(code);
}

template<typename Handler>
Handler MsgHandlerRepository<Handler>::handler(const std::string& code) const
{
    typename HandlerMap::const_iterator i = this->handlers.find(code);
    return i != this->handlers.end() ? i->second : Handler();
}

template<typename Handler>
MsgHandlerRepository<Handler>::MsgHandlerRepository()
{
}

template<typename Handler>
MsgHandlerRepository<Handler>::MsgHandlerRepository(
        const MsgHandlerRepository<Handler>& other)
{
}

template<typename Handler>
MsgHandlerRepository<Handler>& MsgHandlerRepository<Handler>::operator=(
        const MsgHandlerRepository<Handler>& other)
{
    return *this;
}

} } // GreenLeaf::GLNetIO

