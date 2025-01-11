#include "config_loader.hpp"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

ConfigLoader::ConfigLoader(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening config file: " << filename << std::endl;
        return;
    }
    json j;
    file >> j;
    for (auto& el : j.items()) {
        config[el.key()] = el.value().dump();
    }
}

std::map<std::string, std::string> ConfigLoader::getConfig() {
    return config;
}