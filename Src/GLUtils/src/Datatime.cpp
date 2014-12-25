/*
 * Datatime.cpp
 *
 *  Created on: Dec 19, 2014
 *      Author: wim
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "GreenLeaf/GLUtils/Datatime.h"

namespace GreenLeaf {
namespace GLUtils {

Datatime& Datatime::instance()
{
    static Datatime _gInstance;
    return _gInstance;
}

Datatime::Datatime()
{
}

const std::string Datatime::localDatatimeF()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F", now);

    return std::string(ds);
}

const std::string Datatime::localDatatimeT()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%T", now);

    return std::string(ds);
}

const std::string Datatime::localDatatimeFT()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F %T", now);

    return std::string(ds);
}

const std::string Datatime::localDatatimeFTZ()
{
    time_t t = std::time(0);
    tm* now = std::localtime(&t);
    char ds[30];
    std::strftime(ds, sizeof(ds), "%F %T %Z", now);

    return std::string(ds);
}

} } // GreenLeaf::GLUtils

