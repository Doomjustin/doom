#include <doom/Configuration.h>

#include <cstdlib>
#include <iostream>

doom::Configuration configuration{ doom::from_project_dir("test/test_property.json") };

int main()
{
    auto& log_config = configuration.log_config();

    std::cout << log_config.name << '\n'
              << log_config.level << '\n'
              << log_config.pattern << std::endl;

    return EXIT_SUCCESS;
}