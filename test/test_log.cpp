#include <doom/Log.h>

#include <cstdlib>


int main()
{
    DOOM_LOG_DEBUG("test {}", 12);
    DOOM_LOG_INFO("test {}", 12);
    DOOM_LOG_WARN("test {}", 12);
    DOOM_LOG_ERROR("test {}", 12);
    DOOM_LOG_FATAL("test {}", 12);

    DOOM_LOG_LEVEL(doom::LogLevel::Debug);

    DOOM_LOG_DEBUG("test {}", 12);
    DOOM_LOG_INFO("test {}", 12);
    DOOM_LOG_WARN("test {}", 12);
    DOOM_LOG_ERROR("test {}", 12);
    DOOM_LOG_FATAL("test {}", 12);


    return EXIT_SUCCESS;
}