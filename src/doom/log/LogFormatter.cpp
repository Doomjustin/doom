#include "LogFormatter.h"
#include "doom/Charset.h"

#include <sstream>
#include <ctime>

namespace doom {

class StringItem: public LogFormatter::FormatItem {
public:
    explicit StringItem(std::string str)
      : LogFormatter::FormatItem{},
        str_{ std::move(str) }
    {}

    void format(std::ostream& os, [[maybe_unused]] const LogEvent& event) const noexcept override
    {
        os << str_;
    }

private:
    std::string str_;
};

class MessageItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.message;
    }
};

class LogLevelItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.level;
    }
};

class ElapsedTimeItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.elapse;
    }
};

class LoggerNameItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.logger_name;
    }
};

class ThreadIDItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.thread_id;
    }
};

class NewLineItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, [[maybe_unused]] const LogEvent& event) const noexcept override
    {
        os << NEWLINE;
    }
};

class DateTimeItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        char buffer[100];

#pragma GCC diagnostic ignored "-Wformat-nonliteral"
        std::strftime(buffer,
                      sizeof(buffer),
                      subpattern_.c_str(),
                      std::localtime(&event.time));
#pragma GCC diagnostic warning "-Wformat-nonliteral"

        os << buffer;
    }

    void subpattern(std::string_view value) noexcept override
    {
        subpattern_ = value;
    }

private:
    std::string subpattern_ = "%Y-%m-%d %H:%M:%S";
};

class FileNameItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.file_name;
    }
};

class FunctionNameItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.function_name;
    }
};

class LineItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.line;
    }
};

class ColumnItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.column;
    }
};

class TabItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, [[maybe_unused]] const LogEvent& event) const noexcept override
    {
        os << TAB;
    }
};

class FiberIDItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.fiber_id;
    }
};

class ThreadNameItem: public LogFormatter::FormatItem {
public:
    void format(std::ostream& os, const LogEvent& event) const noexcept override
    {
        os << event.thread_name;
    }
};


LogFormatter::LogFormatter(std::string pattern)
  : pattern_{ std::move(pattern) }
{
    parse();
}

std::string LogFormatter::format(const LogEvent& event) const noexcept
{
    std::stringstream ss{};
    for (auto& item: fmt_)
        item->format(ss, event);

    return ss.str();
}

void LogFormatter::pattern(std::string_view value) noexcept
{
    pattern_ = value;
    parse();
}

void LogFormatter::parse()
{
    fmt_.clear();
    static constexpr char PATTERN_ITEM_LEADER = PERCENTAGE;

    std::size_t cur_pos = 0;
    while (cur_pos < pattern_.size()) {
        // 需要格式替换
        if (pattern_[cur_pos] == PATTERN_ITEM_LEADER) {
            ++cur_pos;

            char item_flag = pattern_[cur_pos];
            fmt_.emplace_back(make_item(item_flag));

            ++cur_pos;
            // 定义了subpattern
            if (pattern_[cur_pos] == LEFT_BRACKET) {
                auto right_bracket_pos = pattern_.find(RIGHT_BRACKET, cur_pos);
                if (right_bracket_pos == std::string::npos) {
                    fmt_.emplace_back(std::make_unique<StringItem>("<<ERROR>>"));
                    break;
                }

                fmt_.back()->subpattern(pattern_.substr(cur_pos + 1, right_bracket_pos - cur_pos - 1));
                cur_pos = right_bracket_pos + 1;
            }
        }
        else { // 无需替换，保留原来的值
            auto next_leader = pattern_.find(PATTERN_ITEM_LEADER, cur_pos);
            if (next_leader == std::string::npos) {
                fmt_.emplace_back(std::make_unique<StringItem>(pattern_.substr(cur_pos)));
                break;
            }

            fmt_.emplace_back(std::make_unique<StringItem>(pattern_.substr(cur_pos, next_leader - cur_pos)));
            cur_pos = next_leader;
        }
    }
}

std::unique_ptr<LogFormatter::FormatItem> LogFormatter::make_item(char flag)
{
    switch (flag) {
    case 'm':
        return std::make_unique<MessageItem>();
    case 'p':
        return std::make_unique<LogLevelItem>();
    case 'r':
        return std::make_unique<ElapsedTimeItem>();
    case 'L':
        return std::make_unique<LoggerNameItem>();
    case 't':
        return std::make_unique<ThreadIDItem>();
    case 'n':
        return std::make_unique<NewLineItem>();
    case 'd':
        return std::make_unique<DateTimeItem>();
    case 'F':
        return std::make_unique<FileNameItem>();
    case 'f':
        return std::make_unique<FunctionNameItem>();
    case 'l':
        return std::make_unique<LineItem>();
    case 'c':
        return std::make_unique<ColumnItem>();
    case 'T':
        return std::make_unique<TabItem>();
    case 'C':
        return std::make_unique<FiberIDItem>();
    case 'N':
        return std::make_unique<ThreadNameItem>();
    default:
        return std::make_unique<StringItem>("<<ERROR>>");
    }
}

} // namespace doom