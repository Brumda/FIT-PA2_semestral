#include "freezeEffect.h"

FreezeEffect::FreezeEffect(size_t time, int _slow, bool _applied) :
        TowerEffect(time), slow(_slow), applied(_applied) {}

FreezeEffect::FreezeEffect(size_t time, int _slow) :
        TowerEffect(time), slow(_slow), applied(false) {}

void FreezeEffect::apply(std::shared_ptr<Stats> target) {
    if (!applied) {
        applied = true;
        target->speed -= slow;
    }
    if (--time == 0)
        target->speed += slow;

}

nlohmann::json FreezeEffect::save() const {
    using json = nlohmann::json;
    json effect;
    effect["name"] = "freeze";
    effect["time"] = time;
    effect["applied"] = applied;
    return effect;
}

std::unique_ptr<TowerEffect> FreezeEffect::clone() const {
    return std::make_unique<FreezeEffect>(*this);
}
