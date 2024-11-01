#pragma once

#include "towerEffect.h"
#include <memory>

/**
 * @class FreezeEffect
 * @brief effect that applies the ice tower. Slows the target for some rounds
 * Subclass of TowerEffect
 */
class FreezeEffect : public TowerEffect {
private:
    int slow;     ///< how much should the effect slow its target
    bool applied; ///< if the effect is currently applied
public:
    FreezeEffect(size_t time, int slow);

    FreezeEffect(size_t time, int slow, bool applied);

    std::unique_ptr<TowerEffect> clone() const override;

    /**
     * @brief Slows the attacker for X rounds
     * @param target who is the unlucky frozen guy
     */
    void apply(std::shared_ptr<Stats> target) override;

    /**
     * @brief Saves everything that changes on the effect or is used to recreate it after loading.
     * Saves: name, time, applied
     * @return json object containing all the information
     */
    nlohmann::json save() const override;
};
