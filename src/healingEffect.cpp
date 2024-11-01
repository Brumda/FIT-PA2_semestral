#include "healingEffect.h"

HealingEffect::HealingEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown)
        : AttackerEffect(std::move(name), amount, cooldown, applied, currentCooldown) {}

HealingEffect::HealingEffect(std::string name, int amount, size_t cooldown) : AttackerEffect(std::move(name), amount,
                                                                                             cooldown) {}

std::unique_ptr<AttackerEffect> HealingEffect::clone() const {
    return std::make_unique<HealingEffect>(*this);
}

void HealingEffect::apply(std::shared_ptr<Stats> target) {
    if (--currentCooldown == 0) {
        currentCooldown = cooldown;
        if (target->currentLives < target->maxLives - amount)
            target->currentLives += amount;
        else
            target->currentLives = target->maxLives;
    }
}
