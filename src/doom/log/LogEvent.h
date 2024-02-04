#ifndef DOOM_LOG_EVENT_H
#define DOOM_LOG_EVENT_H

#include "LogLevel.h"

#include <string_view>
#include <cstdint>
#include <thread>

namespace doom {

struct LogEvent {
    std::uint32_t line = 0;
    std::uint32_t column = 0;
    LogLevel level = LogLevel::Debug;
    std::time_t elapse = 0;             // 程序启动到现在的毫秒数
    std::time_t time = 0;               // 这次log的发生时间
    std::thread::id thread_id{};
    std::string_view thread_name;
    std::uint32_t fiber_id = 0;
    std::string_view file_name;
    std::string_view function_name;
    std::string_view logger_name;
    std::string_view message;
};

} // namespace doom

#endif // DOOM_LOG_EVENT_H
