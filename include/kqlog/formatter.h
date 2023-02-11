#ifndef KQLOG_FORMATTER_H
#define KQLOG_FORMATTER_H

#include "common.h"

namespace kq
{
    template<typename T, typename C>
    class formatter
    {
    public:
        using enum_type = T;
        using encoding_type = C;
    public:
        formatter();
        formatter(const formatter& other);
        formatter(formatter&& other) noexcept;
        ~formatter();

        formatter& operator=(const formatter& other); // TODO: implement me
        formatter& operator=(formatter&& other); // TODO: implement me
    private:
        std::vector<std::string> m_args;
        std::string m_fmt;
        enum_type m_type;
    };

    template<typename T, typename C>
    formatter<T, C>::formatter()
        : m_args(), m_fmt()
    {}

    template<typename T, typename C>
    formatter<T, C>::formatter(const formatter& other)
        : m_args(), m_fmt()
    {}

    template<typename T, typename C>
    formatter<T, C>::formatter(formatter&& other) noexcept
        : m_args(), m_fmt()
    {}

    template<typename T, typename C>
    formatter<T, C>::~formatter()
    {}
}

#endif