#ifndef KQLOG_COMMON_H
#define KQLOG_COMMON_H
#if defined (_WIN32)
    #define _OS_COPY "copy "
#elif defined (__linux__)
    #define _OS_COPY "cp "
#endif
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
#include <experimental/source_location>
#include <unordered_map>
#include <algorithm>
#include <ctime>

#endif