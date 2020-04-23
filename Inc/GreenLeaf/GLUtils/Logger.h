/**
 * @file Logger.h
 * @brief 日志工具的声明文件
 * @author Mason
 * @version v1.0
 * @date 2014-12-26
 */
#ifndef LOGGER_H
#define LOGGER_H

#include <boost/format.hpp>
#include <boost/noncopyable.hpp>
#include <boost/thread/mutex.hpp>

namespace GreenLeaf {
namespace GLUtils {

/** 日志等级枚举 */
enum LoggerLevel {
    LL_TRACE = 1, LL_DEBUG, LL_INFO, LL_WARN, LL_ERROR
};

/**
 * @brief 日志工具类
 */
class Logger: boost::noncopyable
{
public:
    static Logger& instance();

    void init(const LoggerLevel& lev, std::ostream* out);
    void resetOut(std::ostream* out);

    void resetLevel(const LoggerLevel& lev);

    template<class A>
    void log(const LoggerLevel& lev, A a) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            *this->_out << a << std::endl;
        }
    }

    template<class A>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A a) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a << std::endl;
        }
    }

    template<class A1, class A2>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 << std::endl;
        }
    }

    template<class A1, class A2, class A3>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4, class A5>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4, A5 a5) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 % a5 << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4, A5 a5, A6 a6) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 % a5 % a6 << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4, A5 a5, A6 a6, A7 a7) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 % a5 % a6 % a7 << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7, class A8>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4, A5 a5, A6 a6, A7 a7, A8 a8) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 % a5 % a6 % a7 % a8
                    << std::endl;
        }
    }

    template<class A1, class A2, class A3, class A4, class A5, class A6,
            class A7, class A8, class A9>
    void log(const LoggerLevel& lev, const std::string& fmtStr, A1 a1, A2 a2, A3 a3,
            A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9) {
        boost::mutex::scoped_lock lock(_mutex);
        if (lev >= this->_level) {
            this->writeDateStr(lev);

            boost::format fmter(fmtStr);
            fmter.exceptions(
                    boost::io::all_error_bits
                            ^ (boost::io::too_many_args_bit
                                    | boost::io::too_few_args_bit));
            *this->_out << fmter % a1 % a2 % a3 % a4 % a5 % a6 % a7 % a8 % a9
                    << std::endl;
        }
    }

private:
    explicit Logger();

    std::string levelToString(const LoggerLevel& lev);
    void writeDateStr(const LoggerLevel& lev);

private:
    LoggerLevel _level;     /**< 日志等级 */
    std::ostream* _out;     /**< 输出流 */
    boost::mutex _mutex;    /**< 多线程所需锁 */

};

} } // GreenLeaf::GLUtils

#endif // LOGGER_H

