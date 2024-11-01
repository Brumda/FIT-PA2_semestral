#include "burnEffect.h"

BurnEffect::BurnEffect(size_t time, int damage) :
        TowerEffect(time), damage(damage) {}

void BurnEffect::apply(std::shared_ptr<Stats> target) {
    --time;
    target->currentLives -= damage;

}

nlohmann::json BurnEffect::save() const {
    using json = nlohmann::json;
    json effect;
    effect["name"] = "burn";
    effect["time"] = time;
    return effect;
}

std::unique_ptr<TowerEffect> BurnEffect::clone() const {
    return std::make_unique<BurnEffect>(*this);
}

