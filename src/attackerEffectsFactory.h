#pragma once

#include "attackerEffect.h"
#include "configLoader.h"
#include <memory>
#include <vector>

/**
 * @class AttackerEffectFactory
 * @brief This class loads the config files and generates all the positive effects for attackers
 */
class AttackerEffectsFactory {
private:
    ConfigLoader config; ///< loaded positive attacker effects data from config
public:
    explicit AttackerEffectsFactory(const std::string &configFile);

    /**
     * @brief Creates corresponding effect
     * @param name of the effect
     * @return new object of the concrete effect
     * @throws runtime_error if the name is not in the config
     */
    std::unique_ptr<AttackerEffect> makeAttackerEffect(const std::string &name);

    /**
     * @brief Overloaded method for loading
     * @param name of the effect
     * @param cooldown current cooldown of the effect when the game was saved
     * @param applied whether the effect was applied when the game was saved
     * @return new object of the concrete effect with loaded values
     * @throws runtime_error if the name is not in the config
     */
    std::unique_ptr<AttackerEffect> makeAttackerEffect(const std::string &name, int cooldown, bool applied);

    const std::vector<std::string> &getPossibilities() const {
        return config.getPossibilities();
    }
    /**
     * @brief Getter for the price
     * @param name of the effect
     * @return the price
     * @throws runtime_error if the name or price is not in the config
     */
    int getPrice(const std::string &name) const;
};
