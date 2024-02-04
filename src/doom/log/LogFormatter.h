#ifndef DOOM_LOG_FORMATTER_H
#define DOOM_LOG_FORMATTER_H

#include "LogEvent.h"

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace doom {

/**
 *  %m 消息
 *  %p 日志级别
 *  %r 累计毫秒数
 *  %L 日志名称
 *  %t 线程id
 *  %n 换行
 *  %d 时间
 *  %F 文件名
 *  %f 函数名
 *  %l 行号
 *  %c 列号
 *  %T 制表符
 *  %C 协程id
 *  %N 线程名称
 *
 *  默认格式 "%d{%Y-%m-%d %H:%M:%S} [%t: %N][%C][%L][%F][%p] [%f %l:%c]: %m%n"
 */
class LogFormatter {
public:
    explicit LogFormatter(std::string pattern = "%d{%Y-%m-%d %H:%M:%S} [%p] [%t: %N][%C][%L][%F] [%f %l:%c]: %m%n");

    LogFormatter(const LogFormatter&) = default;
    LogFormatter& operator=(const LogFormatter&) = default;

    [[nodiscard]] std::string format(const LogEvent& event) const noexcept;

    void pattern(std::string_view value) noexcept;
    [[nodiscard]] std::string pattern() const noexcept { return pattern_; }

    class FormatItem {
    public:
        virtual ~FormatItem() = default;

        virtual void format(std::ostream& os, const LogEvent& event) const noexcept = 0;
        virtual void subpattern([[maybe_unused]] std::string_view value) noexcept {}
    };

private:
    std::string pattern_;
    std::vector<std::unique_ptr<FormatItem>> fmt_;

    void parse();
    static std::unique_ptr<FormatItem> make_item(char flag);
};

} // namespace doom

#endif // DOOM_LOG_FORMATTER_H
