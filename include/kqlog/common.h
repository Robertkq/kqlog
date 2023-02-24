#ifndef KQLOG_COMMON_H
#define KQLOG_COMMON_H

#define FMT_HEADER_ONLY
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <magic_enum.hpp>
#include <fmt/core.h>
#include <fstream>
#include <mutex>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <algorithm>
#include <ctime>

namespace kq
{
    enum class default_symbols : uint8_t
    {
        INFO,
        DEBUG,
        WARNING,
        ERROR,
        CRITICAL
    };
}

#define KQINFO kq::default_symbols::INFO
#define KQDEBUG kq::default_symbols::DEBUG
#define KQWARNING kq::default_symbols::WARNING
#define KQERROR kq::default_symbols::ERROR
#define KQCRITICAL kq::default_symbols::CRITICAL

#if defined (_WIN32)
    #define _OS_COPY "copy "
    #include <windows.h>
#elif defined (__linux__)
    #define _OS_COPY "cp "
    #include <unistd.h>
#endif

#endif