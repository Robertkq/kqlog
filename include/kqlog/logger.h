#ifndef KQLOG_LOGGER_H
#define KQLOG_LOGGER_H

#include "common.h"
#include "formatter.h"

namespace kq
{
    enum class default_symbols
    {
        INFO,
        DEBUG,
        WARNING
    };

    template<typename T = default_symbols, typename C = char>
    class logger
    {
    public:
        using enum_type = T;
        using encoding_type = C;
    public:
        logger();
        logger(const std::string& filename); // TODO: implement me
        logger(const logger& other); // TODO: implement me
        logger(logger&& other) noexcept; // TODO: implement me
        ~logger();

        logger& operator=(const logger& other); // TODO: implement me
        logger& operator=(logger& other); // TODO: implement me

        template<typename... Args>
        void out(enum_type type, const std::string& fmt, Args&&... args)  { // TODO: implement me
            // yyyy-mm-dd time type function line
            // cout << format(fmt, std::forward<Args>(args)...); 
        }

    private:
        // std::mutex m_mutex; // TODO: implement me
    };

    template<typename T, typename C>
    logger<T, C>::logger()
    {
        
    }

    template<typename T, typename C>
    logger<T, C>::~logger()
    {
        
    }

} // namespace kq

#endif // KQLOGGER_