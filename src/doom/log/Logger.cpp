#include "Logger.h"

namespace doom {

Logger::Logger(std::string name)
  : name_{ std::move(name) },
    formatter_{ std::make_unique<LogFormatter>() }
{}

void Logger::debug(std::unique_ptr<LogEvent> event)
{
    log(LogLevel::Debug, std::move(event));
}

void Logger::info(std::unique_ptr<LogEvent> event)
{
    log(LogLevel::Info, std::move(event));
}

void Logger::warning(std::unique_ptr<LogEvent> event)
{
    log(LogLevel::Warning, std::move(event));
}

void Logger::error(std::unique_ptr<LogEvent> event)
{
    log(LogLevel::Error, std::move(event));
}

void Logger::fatal(std::unique_ptr<LogEvent> event)
{
    log(LogLevel::Fatal, std::move(event));
}

void Logger::log(LogLevel level, std::unique_ptr<LogEvent> event)
{
    event->logger_name = name_;
    event->level = level;
    event->thread_id = std::this_thread::get_id();

    if (level >= level_)
        // 此调用结束时，event被销毁
        for (auto& appender: appenders_)
            appender->log(*event);
}

void Logger::add_appender(std::unique_ptr<LogAppender> appender)
{
    appender->formatter(formatter_.get());
    appenders_.push_back(std::move(appender));
}

void Logger::pattern(std::string_view value) noexcept
{
    formatter_->pattern(value);
}

} // namespace doom