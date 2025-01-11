#ifndef CONFIG_LOADER_HPP
#define CONFIG_LOADER_HPP

#include <string>
#include <map>

class ConfigLoader {
public:
    ConfigLoader(const std::string& filename);
    std::map<std::string, std::string> getConfig();

private:
    std::map<std::string, std::string> config;
};

#endif // CONFIG_LOADER_HPP