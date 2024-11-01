#pragma once

#include "libs/json.hpp"
#include "towerEffect.h"
#include "attackerEffect.h"
#include "pathFinding.h"
#include "stats.h"

/**
 * @class Attacker
 * @brief Class for attackers that really want to destroy the peaceful life of the towers
 * Good guys in this game
 */
class Attacker {
private:
    char symbol;                                                  ///< symbol representing the attacker on the map
    std::string name;                                             ///< type of the attacker
    std::shared_ptr<Stats> stats;                                 ///< Pointer to the class that has stats of the attacker
    std::pair<int, int> coordinates;                              ///< current position
    std::queue<std::pair<int, int>> path;                         ///< path to destination
    std::unique_ptr<PathFinding> pathFinder;                      ///< pointer to the class that manages movement of the attackers
    std::vector<std::unique_ptr<TowerEffect>> negativeEffects;    ///< active negative Effects
    std::vector<std::unique_ptr<AttackerEffect>> positiveEffects; ///< positive effects
    /**
     * @brief Auxiliary method for swapping. Used with operator =
     * @param other from whom to steal
     */
    void swap(Attacker &other);

public:
    Attacker(std::string name, char symbol, int maxLives, int damage, int speed, int armor,
             const std::pair<int, int> &coordinates, std::unique_ptr<PathFinding> _pathFinder);

    Attacker(std::string name, char symbol, int maxLives, int damage, int speed, int armor,
             const std::pair<int, int> &coordinates, std::unique_ptr<PathFinding> _pathFinder, int currentLives);

    ~Attacker() noexcept = default;

    Attacker(const Attacker &src);

    Attacker &operator=(Attacker src);

    /**
     * @brief Reduces the attackers lives by damage reduced by armor
     * @param damage how much damage did the attacker take
     */
    void takeDamage(int damage);

    /**
     * @brief Calculates path to the destination
     */
    void recalculatePath();

    /**
     * @brief Moves the attacker to the new coordinates
     * @return how much damage did the attacker do, if he reached the base
     */
    int move();

    /**
     * @brief Call this method in the game cycle. Manages what attacker does in the turn
     * @param baseLives lives of the base to deal damage to
     * @return whether the attacker should still exist or not
     */
    bool update(int &baseLives);

    /**
     * @brief Saves everything that changes on the attacker or is used to create him after loading.
     * Saves: name, lives, speed, armor, coordinates, all the effects including their state
     *
     * @return json object containing all the information
     */
    nlohmann::json save() const;

    /**
     * @brief Adds negative effect
     * @param effect
     */
    void addEffect(std::unique_ptr<TowerEffect> effect);

    /**
     * @brief Adds positive effect
     * @param effect
     */
    void addEffect(std::unique_ptr<AttackerEffect> effect);


    const std::pair<int, int> &getCoordinates() const {
        return coordinates;
    }

    char getSymbol() const {
        return symbol;
    }

    bool isAlive() const {
        return stats->currentLives > 0;
    }
};
