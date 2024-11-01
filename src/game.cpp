#include "game.h"
#include "libs/json.hpp"
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cfloat>
#include <filesystem>
#include <utility>

using namespace std;

// Auxiliary function for calculating Euclidean distance
static double euclideanDistance(const pair<int, int> &coord1, const pair<int, int> &coord2) {
    double deltaX = coord2.first - coord1.first;
    double deltaY = coord2.second - coord1.second;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

Game::Game(const std::string &_configPath, std::string _saveFilesPath) :
        config(_configPath + "gameConfig.json"),
        configPath(_configPath),
        towerFactory(configPath + "towers.json"),
        saveFilesPath(std::move(_saveFilesPath)),
        attackerFactory(configPath + "attackers.json"),
        towerEffectFactory(configPath + "towerEffects.json"),
        attackerEffectsFactory(configPath + "attackerEffects.json"),
        input(&spent, &playerMoney, &attackerFactory, &attackerEffectsFactory, &attackersQueue),
        screen(&lives, &round, config.getData().value("maxRound", 50),
               config.getData().value("baseLives", 100),
               &playerMoney, &towers, &attackers) {

    lives = config.getData().value("baseLives", 100);
    playerMoney = config.getData().value("startingMoney", 100);
    moneyPerRound = config.getData().value("moneyPerRound", 50);
    bool flag = false;
    if (!config.getData().contains("towerOrder") ||
        config.getData()["towerOrder"].empty() ||
        config.getData()["towerOrder"].is_null() ||
        config.getData()["towerOrder"] < towerFactory.getPossibilities().size())
        flag = true;
    if (!flag) {
        for (auto &order: towerOrder) {
            if (order >= towerFactory.getPossibilities().size()) {
                flag = true;
                break;
            }
        }
    }
    if (flag) {
        vector<size_t> tmp;
        for (size_t i = 0; i < towerFactory.getPossibilities().size(); ++i)
            tmp.push_back(i);
        towerOrder = tmp;
    } else
        towerOrder = config.getData()["towerOrder"].get<vector<size_t>>();

}

void Game::init(const std::string &_map) {
    map = Map(_map);
    mapPath = _map;
    attackerFactory.setMap(&map);
    input.setMapEntrances(&map.entrances);
    screen.setMap(&map);
}

void Game::newGame(const std::string &_map) {
    init(_map);
    run();
}

// Maybe would deserve its own file
void Game::loadGame(const std::string &fileName) {
    using json = nlohmann::json;
    try {
        std::ifstream file(fileName);
        json jsonData;

        if (file.is_open()) {
            file >> jsonData;
            file.close();
        } else
            throw runtime_error("Corrupted save file");
        auto gameData = jsonData["game"];
        if (gameData.empty() || gameData.is_null()) throw runtime_error("Corrupted save file");

        // Load game
        lives = gameData["lives"];
        spent = gameData["spent"];
        playerMoney = gameData["playerMoney"];
        round = gameData["round"];
        lastTower = gameData["lastTower"];
        init(gameData["map"].get<string>());


        // Load attackers
        json jAttackers = jsonData["attackers"];
        for (auto &att: jAttackers.items()) {
            json attackerData = att.value();
            auto attacker = attackerFactory.makeAttacker(
                    attackerData["name"],
                    attackerData["lives"],
                    attackerData["speed"],
                    attackerData["armor"],
                    attackerData["coordinates"][0],
                    attackerData["coordinates"][1]
            );

            json posEffects = attackerData["posEffects"];
            if (!posEffects.is_null()) {
                for (auto &eff: posEffects.items()) {
                    json effectData = eff.value();
                    auto effect = attackerEffectsFactory.makeAttackerEffect(
                            effectData["name"],
                            effectData["cooldown"],
                            effectData["applied"]);
                    attacker->addEffect(std::move(effect));
                }
            }

            json negEffects = attackerData["negEffects"];
            if (!negEffects.is_null()) {
                for (auto &eff: negEffects.items()) {
                    json effectData = eff.value();
                    auto effect = towerEffectFactory.makeEffect(
                            effectData["name"],
                            effectData["time"],
                            effectData.value("applied", false));
                    attacker->addEffect(std::move(effect));
                }
            }
            attackers.push_back(std::move(attacker));
        }

        // Load towers
        json jTowers = jsonData["towers"];
        for (auto &tow: jTowers.items()) {
            json towerData = tow.value();
            auto tower = towerFactory.makeTower(
                    towerData["name"],
                    towerData["attackCoolDown"],
                    towerData["coordinates"][0],
                    towerData["coordinates"][1]);
            towers.push_back(std::move(tower));
        }
    }
    catch (const json::exception &e) {
        throw runtime_error("Corrupted save file");
    }
    run();
}

// Maybe would deserve its own file
void Game::saveGame() const {
    using json = nlohmann::json;
    json data;

    json game;
    game["lives"] = lives;
    game["spent"] = spent;
    game["playerMoney"] = playerMoney;
    game["round"] = round;
    game["map"] = mapPath;
    game["lastTower"] = lastTower;

    data["game"] = game;

    int a{};
    json jAttackers;
    for (auto &attacker: attackers) {
        auto jAttacker = attacker->save();
        jAttackers["attacker" + to_string(a++)] = jAttacker;

    }
    data["attackers"] = jAttackers;

    int t{};
    json jTowers;
    for (auto &tower: towers) {
        auto jTower = tower->save();
        jTowers["tower" + to_string(t++)] = jTower;

    }
    data["towers"] = jTowers;


    int i{};
    for (const auto &entry: filesystem::directory_iterator(saveFilesPath)) {
        if (entry.is_regular_file())
            ++i;
    }
    ofstream saveFile(saveFilesPath + "/save" + to_string(i + 1) + ".json");
    if (saveFile.is_open()) {
        saveFile << data.dump(2);
        saveFile.close();
    } else
        cout << "Saving failed" << endl;
}


bool Game::chooseEntry(size_t &entrance) const {
    screen.redraw();
    return input.chooseEntry(entrance);
}

bool Game::chooseAttacker(size_t &entrance) {
    screen.redraw();
    return input.chooseAttacker(entrance);
}


bool Game::playerInput() {
    screen.redraw();
    if (input.saveGame())
        saveGame();
    if (input.exitGame())
        return false;

    size_t entrance;
    screen.redraw();
    while (true) {
        if (!chooseEntry(entrance)) break;
        if (!chooseAttacker(entrance)) break;
    }
    return true;
}

void Game::towerDispenser() {
    auto spawnArea = map.towerSpawnAreas.begin();
    auto best = DBL_MAX;
    for (auto it = spawnArea; it != map.towerSpawnAreas.end(); ++it) {
        if (it->empty) {
            double current = 0;
            for (const auto &attacker: attackers)
                current += euclideanDistance(it->position, attacker->getCoordinates());
            if (current < best) {
                best = current;
                spawnArea = it;
            }
        }
    }
    towers.push_back(towerFactory.makeTower(
            towerFactory.getPossibilities()[towerOrder[lastTower++]],
            spawnArea->position));

    lastTower = lastTower % towerFactory.getPossibilities().size();
    spawnArea->empty = false;
}

void Game::towersUpdate() const {
    for (auto &tower: towers)
        tower->update(attackers);

}

void Game::attackersUpdate() {
    for (size_t i = 0; i < map.entrances.size(); ++i) {
        if (!attackersQueue[i].empty()) {
            attackers.push_back(std::move(attackersQueue[i].front()));
            attackersQueue[i].pop();
        }
    }
    for (auto it = attackers.begin(); it != attackers.end();) {
        if (!(*it)->update(lives))
            it = attackers.erase(it);
        else
            ++it;
    }
}

void Game::run() {
    while (true) {
        screen.redraw();
        if (round > config.getData().value("maxRound", 50)) {
            usleep(600000);
            screen.loseScreen(spent);
            break;
        }
        if (round % config.getData().value("playerInputRound", 5) == 0) {
            playerMoney += moneyPerRound;
            if (!playerInput()) break;
        }
        attackersUpdate();
        if (round % config.getData().value("towersSpawnInterval", 5) == 0)
            towerDispenser();
        towersUpdate();
        if (lives <= 0) {
            screen.redraw();
            usleep(600000);
            screen.winScreen(spent);
            break;
        }
        ++round;
        usleep(400000);
    }
}