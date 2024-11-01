#include "speedBoostEffect.h"

SpeedBoostEffect::SpeedBoostEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown)
        : AttackerEffect(std::move(name), amount, cooldown, applied, currentCooldown) {}

SpeedBoostEffect::SpeedBoostEffect(std::string name, int amount, size_t cooldown) :
        AttackerEffect(std::move(name), amount, cooldown) {}

std::unique_ptr<AttackerEffect> SpeedBoostEffect::clone() const {
    return std::make_unique<SpeedBoostEffect>(*this);
}

void SpeedBoostEffect::apply(std::shared_ptr<Stats> target) {
    if (--currentCooldown == 0 && !applied) {
        currentCooldown = cooldown;
        applied = true;
        target->speed += amount;
    } else if (currentCooldown == 0 && applied) {
        currentCooldown = cooldown;
        applied = false;
        target->speed -= amount;
    }
}
