#pragma once

#include "towerEffect.h"
#include <memory>

/**
 * @class WeaknessEffect
 * @brief effect that applies the corrupting tower. Makes the target loose some armor for some rounds
 * Subclass of TowerEffect
 */
class WeaknessEffect : public TowerEffect {
private:
    bool applied;        ///< if the effect is currently applied
    int armorCorruption; ///< by how much should the attackers armor be lowered
public:
    WeaknessEffect(size_t time, int armorCorruption);

    WeaknessEffect(size_t time, int armorCorruption, bool applied);

    std::unique_ptr<TowerEffect> clone() const override;

    /**
     * @brief Lowers the attackers armor for X rounds
     * @param target who is the unlucky guy with broken armor
     */
    void apply(std::shared_ptr<Stats> target) override;

    /**
     * @brief Saves everything that changes on the effect or is used to recreate it after loading.
     * Saves: name, time, applied
     * @return json object containing all the information
     */
    nlohmann::json save() const override;
};
