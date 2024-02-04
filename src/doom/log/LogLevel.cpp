#include "LogLevel.h"

namespace doom {

std::ostream& operator<<(std::ostream& os, LogLevel level)
{
    switch (level) {
    case LogLevel::Debug:
        return os << "debug";
    case LogLevel::Info:
        return os << "info";
    case LogLevel::Warning:
        return os << "warning";
    case LogLevel::Error:
        return os << "error";
    case LogLevel::Fatal:
        return os << "fatal";
    }

    return os;
}

} // namespace doom