#include "towerEffectFactory.h"
#include "freezeEffect.h"
#include "burnEffect.h"
#include "weaknessEffect.h"
#include <iostream>

using namespace std;

TowerEffectFactory::TowerEffectFactory(const string &configFile) : config(configFile) {}

unique_ptr<TowerEffect> TowerEffectFactory::makeEffect(const string &name) const {
    auto effect = config.getData()[name];
    if (effect.empty())
        cout << name << " is not in the config file. Creating default.";

    if (name == "burn")
        return make_unique<BurnEffect>(effect.value("time", 3), effect.value("damage", 2));
    else if (name == "freeze")
        return make_unique<FreezeEffect>(effect.value("time", 3), effect.value("slow", 2));
    else if (name == "weakness")
        return make_unique<WeaknessEffect>(effect.value("time", 3), effect.value("armorCorruption", 2));

    throw runtime_error(name + " tower effect not found.");
}

std::unique_ptr<TowerEffect> TowerEffectFactory::makeEffect(const string &name, int time, bool applied) const {
    auto effect = config.getData()[name];
    if (effect.empty())
        cout << name << " is not in the config file. Creating default.";

    if (name == "burn")
        return make_unique<BurnEffect>(time, effect.value("damage", 2));
    else if (name == "freeze")
        return make_unique<FreezeEffect>(time, effect.value("slow", 2),
                                         applied);
    else if (name == "weakness")
        return make_unique<WeaknessEffect>(time, effect.value("armorCorruption", 2),
                                           applied);

    throw runtime_error(name + " tower effect not found.");
}
