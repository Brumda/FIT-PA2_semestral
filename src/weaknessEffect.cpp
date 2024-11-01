#include "weaknessEffect.h"

using namespace std;

WeaknessEffect::WeaknessEffect(size_t time, int armorCorruption) :
        TowerEffect(time), applied(false), armorCorruption(armorCorruption) {}

WeaknessEffect::WeaknessEffect(size_t time, int armorCorruption, bool applied) :
        TowerEffect(time), applied(applied), armorCorruption(armorCorruption) {}

void WeaknessEffect::apply(std::shared_ptr<Stats> target) {
    if (!applied) {
        applied = true;
        target->armor -= armorCorruption;
    }
    if (--time == 0)
        target->armor += armorCorruption;

}

std::unique_ptr<TowerEffect> WeaknessEffect::clone() const {
    return make_unique<WeaknessEffect>(*this);
}

nlohmann::json WeaknessEffect::save() const {
    using json = nlohmann::json;
    json effect;
    effect["name"] = "weakness";
    effect["time"] = time;
    effect["applied"] = applied;
    return effect;
}
