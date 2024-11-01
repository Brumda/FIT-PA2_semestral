#pragma once

#include "attackerEffectsFactory.h"
#include "handlePlayerInput.h"
#include "attackerFactory.h"
#include "towerFactory.h"
#include "configLoader.h"
#include "screen.h"
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <map>

class Game {
private:
    Map map;                                                             ///< game board
    int lives;                                                           ///< how many lives does the enemy base have left
    int spent = 0;                                                       ///< how much did the player spent so far
    int round = 0;                                                       ///< game round
    int playerMoney;                                                     ///< how much money does the player currently have
    int moneyPerRound;                                                   ///< how much money does the player get per round
    ConfigLoader config;                                                 ///< config values
    std::string mapPath;                                                 ///< which map file is the game using
    size_t lastTower = 0;                                                ///< last tower the AI built
    std::string configPath;                                              ///< path to the config files directory
    TowerFactory towerFactory;                                           ///< manages creating towers
    std::string saveFilesPath;                                           ///< path to the save files directory
    std::vector<size_t> towerOrder;                                      ///< in what order should the AI build the towers
    AttackerFactory attackerFactory;                                     ///< manages creating attackers
    TowerEffectFactory towerEffectFactory;                               ///< manages creating negative effects
    std::vector<std::unique_ptr<Tower>> towers;                          ///< pointers to towers
    AttackerEffectsFactory attackerEffectsFactory;                       ///< manages creating negativeEffects for attackers
    std::vector<std::shared_ptr<Attacker>> attackers;                    ///< pointers to attackers
    std::map<int, std::queue<std::shared_ptr<Attacker>>> attackersQueue; ///< queue of attackers the player chose to send to each entrance
    HandlePlayerInput input;                                             ///< player input wrapper
    Screen screen;                                                       ///< game screen
    // *sad indentation noises*
public:
    Game(const std::string &_configPath, std::string _saveFilesPath);

    /**
     * @brief Starts new game
     * @param _map that the player chose to play
     */
    void newGame(const std::string &_map);

    /**
    * @brief Saves the game into a file
    */
    void saveGame() const;

    /**
     * @brief Loads the game from a file
     * @throws runtime_error if the file is corrupted
     */
    void loadGame(const std::string &fileName);

    /**
     * @brief Player input wrapper
     * @return whether the user wants to continue playing
     */
    bool playerInput();

    /**
     * @brief Gets entry point from player input
     * @return whether the user wants to continue choosing
     */
    bool chooseEntry(size_t &entrance) const;

    /**
     * @brief Gets attacker type from player input
     * @return whether the user wants to continue choosing
     */
    bool chooseAttacker(size_t &entrance);

    /**
     * @brief Simple AI for tower placement based on euclidean distance from all the attackers
     */
    void towerDispenser();

    /**
     * @brief update loop for towers
     */
    void towersUpdate() const;

    /**
    * @brief update loop for attackers
    */
    void attackersUpdate();

    /**
     * @brief Main game loop. Takes user input,
     * creates attackers accordingly, creates new towers, updates attackers and towers
     */
    void run();

    /**
     * @brief Initializes everything map related
     */
    void init(const std::string &_map);
};
