#pragma once

#include "map.h"
#include <queue>
#include <memory>

/**
 * @class PathFinding
 * @brief Class that manages the movement of the attackers
 */
class PathFinding {
protected:
    bool climb;     ///< whether the attacker can climb
    const Map *map; ///< Game board
    static constexpr std::pair<int, int> directions[4] = {{-1, 0},
                                                          {0,  1},
                                                          {1,  0},
                                                          {0,  -1}}; ///< All possible directions the attacker could try to go

public:
    PathFinding(const Map *map, bool climb);

    std::unique_ptr<PathFinding> clone() const;

    /**
     * @brief Determines where the attacker should go next
     * @param currentPosition where is the attacker now
     * @param climb whether can the attacker climb
     * @return path to the destination
     */
    std::queue<std::pair<int, int>> findPath(const std::pair<int, int> &currentPosition) const;

};
