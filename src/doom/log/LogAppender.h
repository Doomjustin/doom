#ifndef DOOM_LOG_APPENDER_H
#define DOOM_LOG_APPENDER_H

#include "LogLevel.h"
#include "LogEvent.h"
#include "LogFormatter.h"

#include <memory>
#include <utility>

namespace doom {

class LogAppender {
public:
    explicit LogAppender(const LogFormatter* formatter)
      : formatter_{ formatter }
    {}

    virtual ~LogAppender() = default;

    virtual void log(const LogEvent& event) = 0;

    void formatter(const LogFormatter* value) noexcept
    {
        formatter_ = value;
    }

protected:
    const LogFormatter* formatter_;
};

} // namespace doom

#endif // DOOM_LOG_APPENDER_H
