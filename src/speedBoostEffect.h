#pragma once

#include "attackerEffect.h"
#include <string>
#include <memory>

/**
 * @class SpeedBoostEffect
 * @brief positive attacker effect that speeds him up for X rounds every X rounds
 * Subclass of AttackerEffect
 */
class SpeedBoostEffect : public AttackerEffect {
public:
    SpeedBoostEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown);

    SpeedBoostEffect(std::string name, int amount, size_t cooldown);

    std::unique_ptr<AttackerEffect> clone() const override;

    /**
     * @brief Every X rounds speeds up the attacker
     * @param target who is supposed to get the speed boost
     */
    void apply(std::shared_ptr<Stats> target) override;
};

