#ifndef DOOM_STDOUT_LOG_APPENDER_H
#define DOOM_STDOUT_LOG_APPENDER_H

#include "LogAppender.h"

namespace doom {

class StdoutLogAppender: public LogAppender {
public:
    explicit StdoutLogAppender(const LogFormatter* formatter = nullptr)
      : LogAppender{ formatter }
    {}

    void log(const LogEvent& event) override;
};

} // namespace doom

#endif // DOOM_STDOUT_LOG_APPENDER_H
