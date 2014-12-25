/*
 * Datatime.h
 *
 *  Created on: Dec 19, 2014
 *      Author: wim
 */

#ifndef DATATIME_H
#define DATATIME_H

#include <boost/noncopyable.hpp>

namespace GreenLeaf {
namespace GLUtils {

class Datatime: private boost::noncopyable
{
public:
    static Datatime& instance();

    const std::string localDatatimeF();
    const std::string localDatatimeT();
    const std::string localDatatimeFT();
    const std::string localDatatimeFTZ();

private:
    explicit Datatime();

};

} } // GreenLeaf::GLUtils

#endif // DATATIME_H

