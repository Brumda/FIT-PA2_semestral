#include "attackerEffectsFactory.h"
#include "healingEffect.h"
#include "speedBoostEffect.h"
#include "armorBuffEffect.h"
#include <iostream>

using namespace std;

AttackerEffectsFactory::AttackerEffectsFactory(const string &configFile) : config(configFile) {}

unique_ptr<AttackerEffect> AttackerEffectsFactory::makeAttackerEffect(const string &name) {
    auto effect = config.getData()[name];

    if (!effect.contains("amount") || !effect.contains("cooldown")) {
        std::cout << name << " is not correct in the config file. Reserving to default value" << std::endl;
    }

    if (name == "healing")
        return make_unique<HealingEffect>("healing", effect.value("amount", 3), effect.value("cooldown", 3));
    else if (name == "speedBoost")
        return make_unique<SpeedBoostEffect>("speedBoost", effect.value("amount", 3), effect.value("cooldown", 3));
    else if (name == "armorBuff")
        return make_unique<ArmorBuffEffect>("armorBuff", effect.value("amount", 3), effect.value("cooldown", 3));

    throw runtime_error(name + " attacker effect not found.");
}

std::unique_ptr<AttackerEffect>
AttackerEffectsFactory::makeAttackerEffect(const string &name, int cooldown, bool applied) {
    auto effect = config.getData()[name];
    if (!effect.contains("amount") || !effect.contains("cooldown")) {
        std::cout << name << " is not correct in the config file. Reserving to default value" << std::endl;
    }
    if (name == "healing")
        return make_unique<HealingEffect>("healing",
                                          effect.value("amount", 3),
                                          effect.value("cooldown", 3),
                                          applied,
                                          cooldown);
    else if (name == "speedBoost")
        return make_unique<SpeedBoostEffect>("speedBoost",
                                             effect.value("amount", 3),
                                             effect.value("cooldown", 3),
                                             applied,
                                             cooldown);
    else if (name == "armorBuff")
        return make_unique<ArmorBuffEffect>("armorBuff",
                                            effect.value("amount", 3),
                                            effect.value("cooldown", 3),
                                            applied,
                                            cooldown);

    throw runtime_error(name + " attacker effect not found.");
}

int AttackerEffectsFactory::getPrice(const string &name) const {
    if (config.getData().contains(name) && config.getData()[name].contains("price"))
        return config.getData()[name]["price"];
    throw std::runtime_error("Corrupted config");
}
