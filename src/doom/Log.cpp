#include "Log.h"
#include "log/Logger.h"
#include "log/StdoutLogAppender.h"
#include "log/FileLogAppender.h"
#include "StaticInfo.h"

#include <filesystem>
#include <atomic>

namespace doom::log {

namespace internal {

// C++20之后，默认构造函数等同于设置ATOMIC_FLAG_INIT
static std::atomic_flag lock{};

Logger& default_logger(std::string name)
{
    static Logger root_logger{ std::move(name) };

    if (!lock.test_and_set(std::memory_order_relaxed)) {
        static std::filesystem::path root_log_file_path{doom::PROJECT_DIR };
        root_log_file_path /= "log/root.log";

        root_logger.add_appender(std::make_unique<StdoutLogAppender>());
        root_logger.add_appender(std::make_unique<FileLogAppender>(root_log_file_path.string()));
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
