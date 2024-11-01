#pragma once

#include "attackerFactory.h"
#include "attackerEffectsFactory.h"
#include <memory>
#include <vector>
#include <queue>
#include <set>
#include <map>

/**
 * @class HandlePlayerInput
 * @brief Auxiliary class that handles player inputs
 */
class HandlePlayerInput {
private:
    int *spent;                                                           ///< pointer to spent money by player
    int *playerMoney;                                                     ///< pointer to players money
    AttackerFactory *attackerFactory;                                     ///< pointer to attacker factory from game
    AttackerEffectsFactory *attackerEffectsFactory;                       ///< pointer to positive attacker effects factory from game
    const std::vector<std::pair<int, int>> *mapEntrances{};               ///< pointer to map entrances
    std::map<int, std::queue<std::shared_ptr<Attacker>>> *attackersQueue; ///< pointer to attacker queue from game
public:
    HandlePlayerInput(int *spent, int *playerMoney, AttackerFactory *_attackerFactory,
                      AttackerEffectsFactory *_attackerEffectsFactory,
                      std::map<int, std::queue<std::shared_ptr<Attacker>>> *_attackersQueue);

    /**
     * @brief Gets user input and lets him choose map entry for his attack
     * @param entrance which entrance he chose
     * @return whether he wants to continue choosing
     */
    bool chooseEntry(size_t &entrance) const;

    /**
     * @brief Gets user input and lets him choose attacker type for his attack
     * @param entrance which entrance he chose before
     * @return whether he wants to continue choosing
     */
    bool chooseAttacker(size_t &entrance);

    /**
     * @brief Gets user input and lets him choose effect type for his attacker
     * @param applied which effects were already used
     * @return new effect to add to the attacker
     */
    std::unique_ptr<AttackerEffect> chooseEffect(std::set<size_t> &applied);

    void setMapEntrances(const std::vector<std::pair<int, int>> *_mapEntrances) {
        mapEntrances = _mapEntrances;
    }

    /**
     * @brief Gets user input about saving the game
     * @return whether the user wants to save the game
     */
    bool saveGame();

    /**
     * @brief Gets user input about exiting the game
     * @return whether the user wants to exit the game
     */
    bool exitGame();
};
