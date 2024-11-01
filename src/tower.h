#pragma once

#include "attacker.h"
#include <memory>
#include <vector>

/**
 * @class Tower
 * @brief Class for towers. Towers attack the attackers in last effort to defend their home.
 * They are the bad guys in this game
 */
class Tower {
private:
    int range;                                         ///< range of the tower
    int damage;                                        ///< how much damage the tower deals
    char symbol;                                       ///< symbol representing the tower
    int attackSpeed;                                   ///< how fast the tower shoots
    std::string name;                                  ///< what type of tower is it
    int attackCoolDown = 0;                            ///< how long until next attack
    std::pair<int, int> coordinates;                   ///< tower position
    std::vector<std::unique_ptr<TowerEffect>> effects; ///< negative effects tower applies on hit
public:
    Tower(int _range, int _damage, char _symbol, int _attackSpeed, const std::pair<int, int> &coordinates,
          std::vector<std::unique_ptr<TowerEffect>> _effects, std::string name);

    Tower(int _range, int _damage, char _symbol, int _attackSpeed, int attackCooldown,
          const std::pair<int, int> &coordinates,
          std::vector<std::unique_ptr<TowerEffect>> _effects, std::string name);

    virtual ~Tower() noexcept = default;

    /**
     * @brief Method for attacking on the attackers aka "the UNO reverse card".
     * Also applies all the effects it can
     * @param target which attacker to attack
     */
    void attack(const std::shared_ptr<Attacker> &target) const;


    /**
     * @brief Call this method in the game cycle.
     * Manages what tower does in the turn
     * @param attackers all the attackers that the tower could attack
     */
    void update(const std::vector<std::shared_ptr<Attacker>> &attackers);

    /**
     * @brief Saves everything that changes on the tower or is used to create it after loading.
     * Saves: name, coordinates, attackCoolDown
     *
     * @return json object containing all the information
     */
    nlohmann::json save() const;


    char getSymbol() const {
        return symbol;
    }

    const std::pair<int, int> &getCoordinates() const {
        return coordinates;
    }
};