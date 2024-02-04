#include "FileLogAppender.h"


namespace doom {

FileLogAppender::FileLogAppender(std::string file_name, const LogFormatter* formatter)
  : LogAppender{ formatter },
    file_name_{ std::move(file_name) },
    file_stream_{ file_name_, std::ios::app }
{}

FileLogAppender::~FileLogAppender()
{
    if (file_stream_) file_stream_.close();
}

void FileLogAppender::log(const LogEvent& event)
{
    file_stream_ << formatter_->format(event);
}

bool FileLogAppender::reopen() noexcept
{
    if (file_stream_)
        file_stream_.close();

    file_stream_.open(file_name_, std::ios::app);
    return static_cast<bool>(file_stream_);
}

} // namespace doom