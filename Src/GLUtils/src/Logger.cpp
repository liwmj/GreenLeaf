/*
 * Logger.cpp
 *
 *  Created on: Nov 6, 2014
 *      Author: wim
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "GreenLeaf/GLUtils/Datatime.h"
#include "GreenLeaf/GLUtils/Logger.h"

namespace GreenLeaf {
namespace GLUtils {

Logger::Logger() :
        _level(LL_TRACE),
        _out(NULL)
{
}

Logger& Logger::instance()
{
    static Logger _gInstance;
    return _gInstance;
}

void Logger::init(const LoggerLevel& lev, std::ostream* out)
{
    _level = lev;
    _out = out;
}

void Logger::resetOut(std::ostream* out) {
    std::ofstream* tmp = dynamic_cast<std::ofstream*>(_out);
    if (NULL != tmp)
        tmp->close();

    _out = out;
}

void Logger::resetLevel(const LoggerLevel& lev)
{
    _level = lev;
}

std::string Logger::levelToString(const LoggerLevel& lev)
{
    switch (lev) {
    case LL_TRACE:
        return "TRACE";
    case LL_DEBUG:
        return "DEBUG";
    case LL_INFO:
        return "INFO";
    case LL_WARN:
        return "WARN";
    default:
        return "ERROR";
    }
}

void Logger::writeDateStr(const LoggerLevel& lev)
{
    if (NULL != _out)
        *_out << Datatime::instance().localDatatimeFTZ().c_str() <<
        " [" << std::right << std::setw(5) << levelToString(lev) << "] ";
}

} } // GreenLeaf::GLUtils

