#pragma once

#include "attackerEffect.h"
#include <string>
#include <memory>
/**
 * @class HealingEffect
 * @brief positive attacker effect that heals him for X rounds every X rounds
 * Subclass of AttackerEffect
 */
class HealingEffect : public AttackerEffect {
public:
    HealingEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown);

    HealingEffect(std::string name, int amount, size_t cooldown);

    std::unique_ptr<AttackerEffect> clone() const override;

    /**
     * @brief Every X rounds starts to heal the attacker
     * @param target who is supposed to get healed
     */
    void apply(std::shared_ptr<Stats> target) override;
};
