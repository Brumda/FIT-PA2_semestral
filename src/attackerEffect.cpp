#include "attackerEffect.h"

AttackerEffect::AttackerEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown) :
        amount(amount), cooldown(cooldown), name(std::move(name)), applied(applied), currentCooldown(currentCooldown) {}

AttackerEffect::AttackerEffect(std::string name, int amount, size_t cooldown) :
        amount(amount), cooldown(cooldown), name(std::move(name)), currentCooldown(cooldown) {}

nlohmann::json AttackerEffect::save() const {
    using json = nlohmann::json;
    json effect;
    effect["name"] = name;
    effect["cooldown"] = currentCooldown;
    effect["applied"] = applied;
    return effect;
}



