#include "armorBuffEffect.h"

ArmorBuffEffect::ArmorBuffEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown)
        : AttackerEffect(std::move(name), amount, cooldown, applied, currentCooldown) {}

ArmorBuffEffect::ArmorBuffEffect(std::string name, int amount, size_t cooldown) :
        AttackerEffect(std::move(name), amount, cooldown) {}

std::unique_ptr<AttackerEffect> ArmorBuffEffect::clone() const {
    return std::make_unique<ArmorBuffEffect>(*this);
}

void ArmorBuffEffect::apply(std::shared_ptr<Stats> target) {
    if (--currentCooldown == 0 && !applied) {
        currentCooldown = cooldown;
        applied = true;
        target->armor += amount;
    } else if (currentCooldown == 0 && applied) {
        currentCooldown = cooldown;
        applied = false;
        target->armor -= amount;
    }
}
