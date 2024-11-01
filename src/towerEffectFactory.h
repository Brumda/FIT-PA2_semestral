#pragma once

#include "towerEffect.h"
#include "configLoader.h"
#include <memory>
#include <vector>

/**
 * @class TowerEffectFactory
 * @brief This class loads the config files and generates all the negative effects
 */
class TowerEffectFactory {
private:
    ConfigLoader config; ///< loaded tower effects data from config
public:
    explicit TowerEffectFactory(const std::string &configFile);

    /**
     * @brief Creates corresponding effect
     * @param name of the tower
     * @return new object of the concrete tower
     * @throws runtime_error if the name is not in the config
     */
    std::unique_ptr<TowerEffect> makeEffect(const std::string &name) const;

    /**
     * @brief Creates corresponding effect
     * @param name of the tower
     * @param time current time of the effect when the game was saved
     * @param applied whether the effect was applied when the game was saved
     * @return new object of the concrete effect with loaded values
     * @throws runtime_error if the name is not in the config
     */
    std::unique_ptr<TowerEffect> makeEffect(const std::string &name, int time, bool applied) const;

    const std::vector<std::string> &getPossibilities() const {
        return config.getPossibilities();
    }
};
