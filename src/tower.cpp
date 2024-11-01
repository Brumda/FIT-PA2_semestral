#include "tower.h"
#include <valarray>
#include <cfloat>

using namespace std;

static double euclideanDistance(const pair<int, int> &coord1, const pair<int, int> &coord2) {
    double deltaX = coord2.first - coord1.first;
    double deltaY = coord2.second - coord1.second;
    return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}

Tower::Tower(int _range, int _damage, char _symbol, int _attackSpeed, const std::pair<int, int> &coordinates,
             std::vector<std::unique_ptr<TowerEffect>> _effects, std::string name)
        : range(_range), damage(_damage), symbol(_symbol), attackSpeed(_attackSpeed), name(std::move(name)),
          coordinates(coordinates),
          effects(std::move(_effects)) {}

Tower::Tower(int _range, int _damage, char _symbol, int _attackSpeed, int attackCooldown,
             const pair<int, int> &coordinates, std::vector<std::unique_ptr<TowerEffect>> _effects, std::string name)
        : range(_range), damage(_damage), symbol(_symbol), attackSpeed(_attackSpeed), name(std::move(name)),
          attackCoolDown(attackCooldown),
          coordinates(coordinates),
          effects(std::move(_effects)) {}

void Tower::attack(const std::shared_ptr<Attacker> &target) const {
    target->takeDamage(damage);
    for (const auto &effect: effects)
        target->addEffect(effect->clone());
}

void Tower::update(const std::vector<std::shared_ptr<Attacker>> &attackers) {
    if (attackCoolDown == 0) {
        if (!attackers.empty()) {
            auto target = attackers[0];
            attackCoolDown = attackSpeed;
            auto closest = DBL_MAX;
            double current = 0;
            for (const auto &attacker: attackers) {
                current += euclideanDistance(coordinates, attacker->getCoordinates());
                if (current < closest) {
                    closest = current;
                    target = attacker;
                }
            }
            if (range > closest)
                attack(target);
        }
        return;
    }
    --attackCoolDown;
}

nlohmann::json Tower::save() const {
    using json = nlohmann::json;
    json tower;
    tower["name"] = name;
    tower["coordinates"] = coordinates;
    tower["attackCoolDown"] = attackCoolDown;

    return tower;
}

