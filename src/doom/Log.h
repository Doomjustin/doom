#ifndef DOOM_LOG_H
#define DOOM_LOG_H

#include "log/Logger.h"

#include <format>
#include <utility>
#include <source_location>

namespace doom::log {

namespace internal {

Logger& default_logger(std::string name = "root");

std::unique_ptr<LogEvent> make_event(const std::source_location& cur, std::time_t now, std::string_view message);

} // namespace internal

void level(LogLevel value);

void pattern(std::string_view value);

template<typename... T>
void debug(const std::source_location cur, std::time_t now, std::string_view message)
{
    internal::default_logger().debug(internal::make_event(cur, now, message));
}

template<typename... T>
void info(const std::source_location cur, std::time_t now, std::string_view message)
{
    internal::default_logger().info(internal::make_event(cur, now, message));
}

template<typename... T>
void warning(const std::source_location& cur, std::time_t now, std::string_view message)
{
    internal::default_logger().warning(internal::make_event(cur, now, message));
}

template<typename... T>
void error(const std::source_location cur, std::time_t now, std::string_view message)
{
    internal::default_logger().error(internal::make_event(cur, now, message));
}

template<typename... T>
void fatal(const std::source_location cur, std::time_t now, std::string_view message)
{
    internal::default_logger().fatal(internal::make_event(cur, now, message));
}

} // namespace doom::log


#ifdef DOOM_DEBUG
    #define DOOM_LOG_LEVEL(value) doom::log::level(value)

    #define DOOM_LOG_PATTERN(value) doom::log::pattern(value)

    #define DOOM_LOG_DEBUG(...) \
        doom::log::debug(std::source_location::current(), \
                         std::time(nullptr), \
                         std::format(__VA_ARGS__))

    #define DOOM_LOG_INFO(...)  \
        doom::log::info(std::source_location::current(), \
                        std::time(nullptr), \
                        std::format(__VA_ARGS__))

    #define DOOM_LOG_WARN(...)  \
        doom::log::warning(std::source_location::current(), \
                           std::time(nullptr), \
                           std::format(__VA_ARGS__))

    #define DOOM_LOG_ERROR(...) \
        doom::log::error(std::source_location::current(), \
                         std::time(nullptr), \
                         std::format(__VA_ARGS__))

    #define DOOM_LOG_FATAL(...) \
        doom::log::fatal(std::source_location::current(), \
                         std::time(nullptr), \
                         std::format(__VA_ARGS__))
#else
    #define DOOM_LOG_LEVEL(value)
    #define DOOM_LOG_PATTERN(value)
    #define DOOM_LOG_DEBUG(...)
    #define DOOM_LOG_INFO(...)
    #define DOOM_LOG_WARN(...)
    #define DOOM_LOG_ERROR(...)
    #define DOOM_LOG_FATAL(...)
#endif // !DOOM_DEBUG

#endif // DOOM_LOG_H
