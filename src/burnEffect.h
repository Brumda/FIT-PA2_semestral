#pragma once

#include "towerEffect.h"

/**
 * @class BurnEffect
 * @brief effect that applies the fire tower. Makes the target burn (take damage) for some rounds
 * Subclass of TowerEffect
 */
class BurnEffect : public TowerEffect {
protected:
    int damage; ///< how much damage should the burn do
public:
    BurnEffect(size_t time, int damage);

    std::unique_ptr<TowerEffect> clone() const override;

    /**
     * @brief Sets the attacker ablaze for X rounds
     * @param target who is the unlucky guy on fire
     */
    void apply(std::shared_ptr<Stats> target) override;

    /**
     * @brief Saves everything that changes on the effect or is used to recreate it after loading.
     * Saves: name, time
     * @return json object containing all the information
     */
    nlohmann::json save() const override;
};
