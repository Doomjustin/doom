#include "StdoutLogAppender.h"

#include <iostream>

namespace doom {

void StdoutLogAppender::log(const LogEvent& event)
{
    std::cout << formatter_->format(event);
}

} // namespace doom