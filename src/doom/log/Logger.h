#ifndef DOOM_LOGGER_H
#define DOOM_LOGGER_H

#include "LogLevel.h"
#include "LogEvent.h"
#include "LogAppender.h"

#include <string>
#include <string_view>
#include <memory>
#include <vector>

namespace doom {

class Logger {
public:
    explicit Logger(std::string name = "root");

    void debug(std::unique_ptr<LogEvent> event);
    void info(std::unique_ptr<LogEvent> event);
    void warning(std::unique_ptr<LogEvent> event);
    void error(std::unique_ptr<LogEvent> event);
    void fatal(std::unique_ptr<LogEvent> event);

    void log(LogLevel level, std::unique_ptr<LogEvent> event);

    void add_appender(std::unique_ptr<LogAppender> appender);

    void pattern(std::string_view value) noexcept;

    [[nodiscard]] constexpr LogLevel level() const noexcept { return level_; }
    void level(LogLevel value) noexcept { level_ = value; }

private:
    std::string name_;
    LogLevel level_ = LogLevel::Info;
    std::unique_ptr<LogFormatter> formatter_;
    std::vector<std::unique_ptr<LogAppender>> appenders_;
};

} // namespace doom

#endif //DOOM_LOGGER_H
