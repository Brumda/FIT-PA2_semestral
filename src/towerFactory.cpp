#include "towerFactory.h"
#include <iostream>

using namespace std;

TowerFactory::TowerFactory(const string &configFile) :
        config(configFile),
        towerEffectFactory(configFile.substr(0, configFile.find_last_of('/') + 1) + "towerEffects.json") {}

std::unique_ptr<Tower> TowerFactory::makeTower(const std::string &name, const std::pair<int, int> &coordinates) const {
    vector<unique_ptr<TowerEffect>> effects{};
    auto tower = config.getData()[name];
    if (!tower.contains("range") || !tower.contains("damage") || !tower.contains("symbol") ||
        !tower.contains("attackSpeed") || !tower.contains("effect")) {
        cout << name << " is not correct in the config file. Reserving to default value" << endl;
    }
    if (tower.contains("effect") && !tower["effect"].empty()) {
        vector<string> effectNames = tower["effect"].get<std::vector<std::string>>();
        for (const auto &effectName: effectNames) {
            auto effect = towerEffectFactory.makeEffect(effectName);
            if (effect)
                effects.push_back(std::move(effect));
        }
    }
    return make_unique<Tower>(
            tower.value("range", 2),
            tower.value("damage", 3),
            tower["symbol"].empty() ? 'B' : tower["symbol"].get<std::string>()[0], // I hate this so much
            tower.value("attackSpeed", 2),
            coordinates,
            std::move(effects),
            name);
}

std::unique_ptr<Tower>
TowerFactory::makeTower(const string &name, int attackCooldown, int coord1, int coord2) const {
    vector<unique_ptr<TowerEffect>> effects{};
    auto tower = config.getData()[name];
    if (!tower.contains("range") || !tower.contains("damage") || !tower.contains("symbol") ||
        !tower.contains("attackSpeed") || !tower.contains("effect")) {
        cout << name << " is not correct in the config file. Reserving to default value" << endl;
    }
    if (tower.contains("effect") && !tower["effect"].empty()) {
        vector<string> effectNames = tower["effect"].get<std::vector<std::string>>();
        for (const auto &effectName: effectNames) {
            auto effect = towerEffectFactory.makeEffect(effectName);
            if (effect)
                effects.push_back(std::move(effect));
        }
    }
    return make_unique<Tower>(
            tower.value("range", 2),
            tower.value("damage", 3),
            tower["symbol"].empty() ? 'B' : tower["symbol"].get<std::string>()[0], // I hate this so much
            tower.value("attackSpeed", 2),
            attackCooldown,
            std::make_pair(coord1, coord2),
            std::move(effects),
            name);
}
