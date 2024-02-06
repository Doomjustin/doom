#include "Configuration.h"

#include "StaticInfo.h"

#include <fstream>

namespace doom {

std::filesystem::path from_project_dir(const std::string& sub_path)
{
    std::filesystem::path full_path{ PROJECT_DIR };
    return full_path /= sub_path;
}


void to_json(nlohmann::json& j, const LogConfiguration& config)
{
    j = nlohmann::json{ { "name", config.name },
                        { "level", config.level },
                        { "pattern", config.pattern } };
}

void from_json(const nlohmann::json& j, LogConfiguration& config)
{
    j.at("name").get_to(config.name);

    try {
        j.at("level").get_to(config.level);
    }
    catch (...) {
        config.level = LogLevel::Debug;
    }

    try {
        j.at("pattern").get_to(config.pattern);
    }
    catch (...) {
        config.pattern = "%d{%Y-%m-%d %H:%M:%S} [%p] [%t: %N][%C][%L][%F] [%f %l:%c]: %m%n";
    }
}

Configuration::Configuration()
  : path_{ PROJECT_DIR }
{
    path_ /= "src/resource/property.json";
    parse();
}

Configuration::Configuration(std::filesystem::path path)
  : path_{ std::move(path) }
{
    parse();
}

void Configuration::parse()
{
    std::fstream fs{ path_ };
    auto json = nlohmann::json::parse(fs);
    log_config_ = json["log"].template get<LogConfiguration>();
}

} // namespace doom