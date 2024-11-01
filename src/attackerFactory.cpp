#include "attackerFactory.h"
#include <iostream>
#include <stdexcept>

AttackerFactory::AttackerFactory(const std::string &configFile) : config(configFile) {}


std::shared_ptr<Attacker>
AttackerFactory::makeAttacker(const std::string &name, const std::pair<int, int> &_coordinates) const {
    auto attacker = config.getData()[name];
    if (!attacker.contains("symbol") || !attacker.contains("lives") || !attacker.contains("damage") ||
        !attacker.contains("speed") || !attacker.contains("armor") ||
        !attacker.contains("climbs"))
        std::cout << name << " is not correct in the config file. Reserving to default value" << std::endl;

    return std::make_shared<Attacker>(
            name,
            attacker["symbol"].empty() ? 'W' : attacker["symbol"].get<std::string>()[0], // I hate this so much
            attacker.value("lives", 25),
            attacker.value("damage", 10),
            attacker.value("speed", 2),
            attacker.value("armor", 2),
            _coordinates,
            std::make_unique<PathFinding>(map, attacker.value("climbs", false)));
}

std::shared_ptr<Attacker>
AttackerFactory::makeAttacker(const std::string &name, int lives, int speed, int armor, int coord1, int coord2) const {
    auto attacker = config.getData()[name];
    if (!attacker.contains("symbol") || !attacker.contains("lives") || !attacker.contains("damage") ||
        !attacker.contains("climbs")) {
        std::cout << name << " is not correct in the config file. Reserving to default value" << std::endl;
    }

    return std::make_shared<Attacker>(
            name,
            attacker["symbol"].empty() ? 'W' : attacker["symbol"].get<std::string>()[0], // I hate this so much
            attacker.value("lives", 25),
            attacker.value("damage", 10),
            speed,
            armor,
            std::make_pair(coord1, coord2),
            std::make_unique<PathFinding>(map, attacker.value("climbs", false)),
            lives);
}

int AttackerFactory::getPrice(const std::string &name) const {
    if (config.getData().contains(name) && config.getData()[name].contains("price"))
        return config.getData()[name]["price"];
    throw std::runtime_error("Corrupted config");
}
