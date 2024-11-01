#pragma once

#include "tower.h"
#include <string>
#include <memory>
#include <vector>

/**
 * @class Screen
 * @brief Class that handles what the player sees in terminal
 */
class Screen {
private:
    const Map *map{};                                        ///< pointer to game board
    const int *lives;                                        ///< pointer to base lives
    const int *round;                                        ///< pointer to game rounds
    const int maxRound;                                      ///< maximum amount of rounds possible
    const int baseLives;                                     ///< starting lives of the base
    const int *playerMoney;                                  ///< pointer to players money
    const std::vector<std::unique_ptr<Tower>> *towers;       ///< pointer to towers
    const std::vector<std::shared_ptr<Attacker>> *attackers; ///< pointer to attackers
public:
    Screen(const int *lives, const int *round, int maxRound, int baseLives, const int *playerMoney,
           const std::vector<std::unique_ptr<Tower>> *towers, const std::vector<std::shared_ptr<Attacker>> *attackers);

    /**
     * @brief Draws everything from the game into the terminal
     */
    void redraw() const;

    /**
     * @brief Screen that is displayed when the player wins
     * @param spent how much did the player spent
     */
    void winScreen(int spent) const;

    /**
     * @brief Screen that is displayed when the player looses
     * @param spent how much did the player spent
     */
    void loseScreen(int spent) const;

    void setMap(const Map *_map) {
        map = _map;
    }
};
