/*
 * Uuid.h
 *
 *  Created on: Nov 26, 2014
 *      Author: wim
 */

#ifndef UUID_H
#define UUID_H

#include <boost/noncopyable.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace GreenLeaf {
namespace GLUtils {

class Uuid: private boost::noncopyable
{
public:
    static Uuid& instance();

    const std::string randUuidToString();
    const std::string randUuidToStringWithBraces();


private:
    boost::uuids::random_generator _rgen;

};

} } // GreenLeaf::GLUtils

#endif // UUID_H

