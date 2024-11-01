#pragma once

#include "stats.h"
#include "libs/json.hpp"
#include <memory>

/**
 * @class TowerEffect
 * @brief Base class for the negative effects towers inflict on attackers
 */
class TowerEffect {
protected:
    size_t time; ///< for how long is the effect active
public:
    explicit TowerEffect(size_t time) : time(time) {};

    virtual ~TowerEffect() noexcept = default;

    virtual std::unique_ptr<TowerEffect> clone() const = 0;
    /**
     * @brief Abstract class that applies the effect on the attacker
     * @param target on which attacker should the effect be applied
     */
    virtual void apply(std::shared_ptr<Stats> target) = 0;

    /**
     * @brief Saves everything that changes on the effect or is used to create him after loading.
     * Saves: time and everything the subclass needs
     * @return json object containing all the information
     */
    virtual nlohmann::json save() const = 0;

    bool ended() const {
        return time == 0;
    }
};