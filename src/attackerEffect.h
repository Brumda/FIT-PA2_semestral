#pragma once

#include "libs/json.hpp"
#include "stats.h"
#include <memory>
#include <string>

/**
 * @class AttackerEffect
 * @brief Base class for the positive attacker effects
 */
class AttackerEffect {
protected:
    int amount;             ///< how much should the effect affect the attacker
    size_t cooldown;        ///< how often should the effect occur
    std::string name;       ///< name of the effect
    bool applied = false;   ///< whether is the effect applied
    size_t currentCooldown; ///< how many round until the effect does something again
public:
    AttackerEffect(std::string name, int amount, size_t cooldown, bool applied, size_t currentCooldown);

    AttackerEffect(std::string name, int amount, size_t cooldown);

    virtual ~AttackerEffect() noexcept = default;

    virtual std::unique_ptr<AttackerEffect> clone() const = 0;
    /**
     * @brief Abstract class that applies the effect on the attacker
     * @param target on which attacker should the effect be applied
     */
    virtual void apply(std::shared_ptr<Stats> target) = 0;

    /**
     * @brief Saves everything that changes on the effect or is used to create him after loading.
     * Saves: name, currentCooldown, applied
     * @return json object containing all the information
     */
    nlohmann::json save() const;
};
