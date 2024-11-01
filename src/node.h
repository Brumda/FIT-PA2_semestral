#pragma once

#include <utility>
#include <queue>
#include <memory>

/**
 * @class Node
 * @brief auxiliary struct for map traversing
 */
class Node {
public:
    std::pair<int, int> coordinates;         ///< where the node is
    std::queue<std::pair<int, int>> path{}; ///< how to get to the node from the starting position

    std::pair<int, int> operator+(const std::pair<int, int> &l) const {
        return {l.first + coordinates.first, l.second + coordinates.second};
    }
};

