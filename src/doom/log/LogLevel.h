#ifndef DOOM_LOG_LEVEL_H
#define DOOM_LOG_LEVEL_H

#include <cstdint>
#include <ostream>

namespace doom {

enum class LogLevel: std::uint8_t {
    Debug = 1,
    Info = 2,
    Warning = 3,
    Error = 4,
    Fatal = 5
};

std::ostream& operator<<(std::ostream& os, LogLevel level);

} // namespace doom

#endif // DOOM_LOG_LEVEL_H
