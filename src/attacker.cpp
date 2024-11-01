#include "attacker.h"
#include <iostream>

using namespace std;

Attacker::Attacker(std::string name, char symbol, int maxLives, int damage, int speed, int armor,
                   const std::pair<int, int> &coordinates, std::unique_ptr<PathFinding> _pathFinder) :
        symbol(symbol), name(std::move(name)), coordinates(coordinates),
        pathFinder(std::move(_pathFinder)) {
    stats = make_shared<Stats>(maxLives, armor, speed, damage);
    recalculatePath();
}

Attacker::Attacker(std::string name, char symbol, int maxLives, int damage, int speed, int armor,
                   const std::pair<int, int> &coordinates, std::unique_ptr<PathFinding> _pathFinder, int currentLives) :
        symbol(symbol), name(std::move(name)), coordinates(coordinates),
        pathFinder(std::move(_pathFinder)) {
    stats = make_shared<Stats>(maxLives, armor, speed, damage, currentLives);
    recalculatePath();
}

int Attacker::move() {
    for (int i = 0; i < stats->speed; ++i) {
        coordinates = path.front();
        path.pop();
        if (path.empty())
            return stats->damage;
    }
    return 0;
}

void Attacker::takeDamage(int damage) {
    stats->currentLives -= (damage - stats->armor);
}

bool Attacker::update(int &baseLives) {
    for (auto &effect: positiveEffects)
        effect->apply(stats);

    for (auto it = negativeEffects.begin(); it != negativeEffects.end();) {
        (*it)->apply(stats);
        if ((*it)->ended())
            it = negativeEffects.erase(it);
        else
            ++it;
    }

    if (!isAlive())
        return false;
    int doDmg = move();
    baseLives -= doDmg;

    return doDmg == 0;
}

nlohmann::json Attacker::save() const {
    using json = nlohmann::json;
    json jAttacker;
    jAttacker["name"] = name;
    jAttacker["lives"] = stats->currentLives;
    jAttacker["speed"] = stats->speed;
    jAttacker["armor"] = stats->armor;
    jAttacker["coordinates"] = coordinates;
    json jPosEffects;
    int pe{};
    for (auto &effect: positiveEffects) {
        auto jPosEffect = effect->save();
        jPosEffects["effect" + to_string(pe++)] = jPosEffect;
    }
    jAttacker["posEffects"] = jPosEffects;

    json jNegEffects;
    int ne{};
    for (auto &effect: negativeEffects) {
        json jNegEffect = effect->save();
        jNegEffects["effect" + to_string(ne++)] = jNegEffect;
    }
    jAttacker["negEffects"] = jNegEffects;

    return jAttacker;
}

void Attacker::addEffect(unique_ptr<TowerEffect> effect) {
    negativeEffects.push_back(std::move(effect));
}

void Attacker::addEffect(unique_ptr<AttackerEffect> effect) {
    positiveEffects.push_back(std::move(effect));
}

void Attacker::recalculatePath() {
    path = pathFinder->findPath(coordinates);
}

void Attacker::swap(Attacker &other) {
    std::swap(name, other.name);
    std::swap(symbol, other.symbol);
    std::swap(stats, other.stats);
    std::swap(coordinates, other.coordinates);
    std::swap(path, other.path);
    std::swap(pathFinder, other.pathFinder);
    std::swap(negativeEffects, other.negativeEffects);
    std::swap(positiveEffects, other.positiveEffects);
}

Attacker::Attacker(const Attacker &src) :
        Attacker(src.name, src.symbol, src.stats->currentLives, src.stats->damage,
                 src.stats->speed, src.stats->armor, src.coordinates, src.pathFinder->clone()) {
    for (auto &effect: src.positiveEffects)
        positiveEffects.push_back(effect->clone());
    for (auto &effect: src.negativeEffects)
        negativeEffects.push_back(effect->clone());
}

Attacker &Attacker::operator=(Attacker src) {
    swap(src);
    return *this;
}
