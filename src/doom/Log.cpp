#include "Log.h"
#include "log/Logger.h"
#include "log/StdoutLogAppender.h"
#include "log/FileLogAppender.h"
#include "doom/Version.h"

#include <filesystem>

namespace doom::log {

namespace internal {

static bool IS_INITIALIZED = false;

Logger& default_logger(std::string name)
{
    static Logger root_logger{ std::move(name) };

    if (!IS_INITIALIZED) {
        static std::filesystem::path root_log_file_path{doom::PROJECT_DIR };
        root_log_file_path /= "log/root.log";

        root_logger.add_appender(std::make_unique<StdoutLogAppender>());
        root_logger.add_appender(std::make_unique<FileLogAppender>(root_log_file_path.string()));
        IS_INITIALIZED = true;
    }

    return root_logger;
}

std::unique_ptr<LogEvent> make_event(const std::source_location& cur, std::time_t now, std::string_view message)
{
    auto event = std::make_unique<LogEvent>();
    event->message = message;
    event->line = cur.line();
    event->column = cur.column();
    event->file_name = cur.file_name();
    event->function_name = cur.function_name();
    event->time = now;

    return event;
}

} // namespace doom::log::internal


void level(LogLevel value)
{
    internal::default_logger().level(value);
}

void pattern(std::string_view value)
{
    internal::default_logger().pattern(value);
}

} // namespace doom::log
