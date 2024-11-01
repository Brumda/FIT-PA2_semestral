#pragma once

#include "attackerEffect.h"
#include <string>
#include <memory>

/**
 * @class ArmorBuffEffect
 * @brief positive attacker effect that adds armor
 * Subclass of AttackerEffect
 */
class ArmorBuffEffect : public AttackerEffect {
public:
    ArmorBuffEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown);

    ArmorBuffEffect(std::string name, int amount, size_t cooldown);

    std::unique_ptr<AttackerEffect> clone() const override;

    /**
     * @brief adds armor to the attacker for some time
     * @param target whose armor to toughen
     */
    void apply(std::shared_ptr<Stats> target) override;
};
