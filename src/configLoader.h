#pragma once

#include "libs/json.hpp"
#include <string>
#include <vector>

/**
 * @class ConfigLoader
 * @brief Handles config loading
 */
class ConfigLoader {
private:
    nlohmann::json data;                    ///< data from config
    std::vector<std::string> possibilities; ///< available objects
public:
    /**
     * @brief Loads definitions from the config
     * @param configFile path to the file
     */
    explicit ConfigLoader(const std::string &configFile);

    ~ConfigLoader() = default;

    const nlohmann::json &getData() const {
        return data;
    }

    const std::vector<std::string> &getPossibilities() const {
        return possibilities;
    }
};
