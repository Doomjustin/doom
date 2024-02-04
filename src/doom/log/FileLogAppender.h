#ifndef DOOM_FILE_LOG_APPENDER_H
#define DOOM_FILE_LOG_APPENDER_H

#include "LogLevel.h"
#include "LogEvent.h"
#include "LogAppender.h"

#include <fstream>

namespace doom {

// TODO: append write
class FileLogAppender: public LogAppender {
public:
    explicit FileLogAppender(std::string file_name, const LogFormatter* formatter = nullptr);

    ~FileLogAppender();

    void log(const LogEvent& event) override;

    bool reopen() noexcept;

private:
    std::string file_name_;
    std::ofstream file_stream_;
};

} // namespace doom

#endif // DOOM_FILE_LOG_APPENDER_H
