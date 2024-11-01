#pragma once

#include "configLoader.h"
#include "attacker.h"
#include <string>
#include <memory>

/**
 * @class AttackerFactory
 * @brief This class generates all the attackers based on config file
 */
class AttackerFactory {
private:
    Map *map;            ///< pointer to the game board
    ConfigLoader config; ///< loaded attackers data from config
public:
    explicit AttackerFactory(const std::string &configFile);

    /**
     * @brief Creates corresponding attacker
     * @param name of the attacker
     * @return new object of the concrete attacker
     */
    std::shared_ptr<Attacker> makeAttacker(const std::string &name, const std::pair<int, int> &_coordinates) const;

    /**
     * @brief Creates corresponding attacker from loaded file
     * @param name of the attacker
     * @param lives number of lives when the game was saved
     * @param speed speed when the game was saved
     * @param armor armor when the game was saved
     * @param coord1 y axis when the game was saved
     * @param coord2 x axis when the game was saved
     * @return new object of the concrete attacker
     */
    std::shared_ptr<Attacker>
    makeAttacker(const std::string &name, int lives, int speed, int armor, int coord1, int coord2) const;

    const std::vector<std::string> &getPossibilities() const {
        return config.getPossibilities();
    }
    /**
     * @brief Getter for the price
     * @param name of the attacker
     * @return the price
     * @throws runtime_error if the name or price is not in the config
     */
    int getPrice(const std::string &name) const;

    void setMap(Map *_map) {
        map = _map;
    }
};
