#pragma once

#include "towerEffectFactory.h"
#include "tower.h"
#include <string>
#include <memory>
#include <vector>

/**
 * @class TowerFactory
 * @brief This class loads the config files and generates all the towers
 */
class TowerFactory {
private:
    ConfigLoader config;                   ///< loaded towers data from config
    TowerEffectFactory towerEffectFactory; ///< makes the negativeEffects towers use
public:
    explicit TowerFactory(const std::string &configFile);

    /**
     * @brief Creates corresponding tower
     * @param name of the tower
      * @param coordinates where the tower should be build
     * @return new object of the concrete tower
     */
    std::unique_ptr<Tower> makeTower(const std::string &name, const std::pair<int, int> &coordinates) const;

    /**
     * @brief Creates corresponding tower
     * @param name of the tower
     * @param attackCooldown current cooldown of the tower when the game was saved
     * @param coord1 y axis when the game was saved
     * @param coord2 x axis when the game was saved
     * @return new object of the concrete tower
     */
    std::unique_ptr<Tower> makeTower(const std::string &name, int attackCooldown, int coord1, int coord2) const;

    const std::vector<std::string> &getPossibilities() const {
        return config.getPossibilities();
    }
};
