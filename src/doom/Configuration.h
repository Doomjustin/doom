#ifndef DOOM_CONFIGURATION_H
#define DOOM_CONFIGURATION_H

#include "log/LogLevel.h"

#include <nlohmann/json.hpp>

#include <string>
#include <filesystem>

namespace doom {

std::filesystem::path from_project_dir(const std::string& sub_path);

NLOHMANN_JSON_SERIALIZE_ENUM(LogLevel, {
    { LogLevel::Debug, "debug" },
    { LogLevel::Info, "info" },
    { LogLevel::Warning, "warning" },
    { LogLevel::Error, "error" },
    { LogLevel::Fatal, "fatal" }
})

struct LogConfiguration {
    std::string name;
    LogLevel level;
    std::string pattern;
};

void to_json(nlohmann::json& j, const LogConfiguration& config);
void from_json(const nlohmann::json& j, LogConfiguration& config);


class Configuration {
public:
    Configuration();
    explicit Configuration(std::filesystem::path path);

    [[nodiscard]] const LogConfiguration& log_config() const noexcept { return log_config_; }

private:
    std::filesystem::path path_;
    LogConfiguration log_config_;

    void parse();
};

} // namespace doom

#endif //DOOM_CONFIGURATION_H
