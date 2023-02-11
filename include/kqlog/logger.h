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

    };

    template<typename T = default_symbols, typename C = char>
    class logger
    {
    public:
        using enum_type = T;
        using encoding_type = C;
    public:
        logger();
        ~logger();

        logger& operator<<(const formatter<enum_type, encoding_type>& fmt) const;

    private:

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