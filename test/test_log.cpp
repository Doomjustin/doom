#include <doom/Log.h>

#include <cstdlib>
#include <future>

void thread_work()
{
    DOOM_LOG_DEBUG("test {}", 12);
    DOOM_LOG_INFO("test {}", 12);
    DOOM_LOG_WARN("test {}", 12);
    DOOM_LOG_ERROR("test {}", 12);
    DOOM_LOG_FATAL("test {}", 12);
}

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

    auto fut = std::async(std::launch::async, thread_work);
    fut = std::async(std::launch::async, thread_work);
    fut = std::async(std::launch::async, thread_work);

    fut.wait();

    return EXIT_SUCCESS;
}